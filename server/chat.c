#include "chat.h"
#include "cJSON.h"
#include "write_log.h"
#include "message_type.h"
#include "dbhelper.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <hiredis/hiredis.h>

redisContext *g_redis_conn = NULL;  //全局redis连接
void *g_mysql_conn = NULL;  //全局mysql连接

/*******************************************************************************
*  func desc:   init_mysql_conn
*  input param: void
*  out   param: g_mysql_conn
*  retun value: void
********************************************************************************/
void init_mysql_conn(void)
{   
    if (NULL == g_mysql_conn)
    {
        g_mysql_conn = InitDbCon2(MYSQL_LOCAL, MYSQL_USER, MYSQL_PASSWD, 
            MYSQL_PORT, MYSQL_DATABASE);    
    }
    return ;
}




/*
*name:init_redis_connect
*input:void
*return: -1:faild other:success
*/

int init_redis_connect()
{
    g_redis_conn = redisConnect(CONFIG_REDIS_HOST, CONFIG_REDIS_PORT);
    if (g_redis_conn == NULL || g_redis_conn->err) {
        if (g_redis_conn) {
            write_log(LOG_ERROR, "%s", g_redis_conn->errstr);
        } else {
            write_log(LOG_ERROR, "Can't allocate redis context");
        }
        return -1;
    } else {
        write_log(LOG_DEBUG,"init redis conn success");
        return 1;
    }
}

/*
*name:verify_pwd_by_decode
*inputparam:pwd,db_pwd
*return: -1:deal error 0:success 1:password error 
*describe:比较数据库中密码及用户发送的密码。数据库存储的为加密后密码，在此函数中进行运算
*/

int verify_pwd_by_decode(char* pwd, char* db_pwd)
{
    if (NULL == pwd || NULL == db_pwd)
    {
        return -1;
    }

    /*先暂时简单比较*/
    if (0 == strcmp(db_pwd,pwd))
    {
        //密码正确
        return 0;
    }
    return 0;
}

/*
*name:verify_logon_info_from_mysql
*inputparam:id,password
*return: -1:deal error 0:success 1:password/id error 
*describe:logon info verify
*/

int verify_logon_info_from_mysql(int id,char* password,CHAT_CONNECT *chat_conn)
{
    if (id <= 0 || NULL == password || NULL == chat_conn)
    {
        return -1;
    }
    char sql_str[MAX_LEN_SQL_STR]={0};
    struct DbResult *dbResult = NULL;
    int ret = 0;
    char pwd[MAX_LEN_PWD] = {0};

    /*查询pwd*/
    if (NULL == g_mysql_conn)//init
    {
        init_mysql_conn();
        if(NULL == g_mysql_conn)
        {
            write_log(LOG_ERROR,"connect mysql error");
            return -1;
        }    
    }
    snprintf(sql_str, sizeof(sql_str),SQL_SELECT_USERINFO_BY_ID,id);
    write_log(LOG_DEBUG,"%s",sql_str);
    if (NULL != g_mysql_conn)
    {
        //查pwd
        dbResult = CreateDbResult();
        ret = db_QuerySql(g_mysql_conn, dbResult, sql_str);//querys
        write_log(LOG_DEBUG,"g not null %d dbresult %p",ret,dbResult);
        if (1 != ret)
        {
            if (dbResult)
            {
                FreeDbResult(dbResult);
                dbResult = NULL;
            }
            write_log(LOG_ERROR,"not have pwd by id:%d",id);
            return -1;
        }
        if (NULL != dbResult && dbResult->nrow > 0)
        {
            if (NULL != dbResult->rows[0][0])
            {
                write_log(LOG_DEBUG,"userid:%d pwd from mysql is:%s",id,dbResult->rows[0][0]);
                strncpy(pwd,dbResult->rows[0][0],MAX_LEN_PWD);
            } 
            else
            {
                write_log(LOG_ERROR,"not have result by id:%d",id);
                return -1;
            }
            if (NULL != dbResult->rows[0][1])
            {
                strncpy(chat_conn->user_name,dbResult->rows[0][1],MAX_LEN_USERNAME);
            }
            if (NULL != dbResult->rows[0][2])
            {
                strncpy(chat_conn->icon,dbResult->rows[0][2],MAX_LEN_ICON);
            }
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        else
        {
            write_log(LOG_ERROR,"not have result by id:%d",id);
            return -1;
        }
        if (dbResult)
        {
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
    }//mysqlconn
    /*比较pwd*/
    write_log(LOG_DEBUG,"compare begin");
    return verify_pwd_by_decode(password,pwd);
}

/*
*name:write_data_to_socket_fd(void* data,int data_len)
*inputparam:data,data_len
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/
int write_data_to_socket_fd(int fd,void* data,int data_len)
{
    if (NULL == data || 0 == data_len)
    {
        return -1;
    }
    return write(fd,data,data_len);
    return 0;
}

/*
*name:save_user_fd_relation_to_redis
*inputparam:fd,id
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/

int save_user_fd_relation_to_redis(int fd,int id)
{
    /*检测当前账号是否已登录*/
    if (NULL == g_redis_conn)
    {
        //未初始化redis连接
        if (-1 == init_redis_connect())
        {
            //初始化失败，直接返回错误，因为无法断定当前redis情况
            write_log(LOG_ERROR,"redis maybe is die");
            return -1;
        }
    }
    redisReply *reply = redisCommand(g_redis_conn, "get %d",id);
    write_log(LOG_INFO,"redis_cmd:[get %d]",id);
    if (REDIS_REPLY_NIL != reply->type)
    {
        //查到该key，证明该id当前已登录
        write_log(LOG_DEBUG,"the id %d is loging [%d]", id, reply->type);
        freeReplyObject(reply);
        return -1;
    }
    else
    {
        //未查到，将该key插入redis
        reply = redisCommand(g_redis_conn, "set %d %d", id, fd);
        write_log(LOG_DEBUG,"set %d %d", id, fd);
        freeReplyObject(reply);
    }
    return 0;
}



/*
*name:construct_userinfo_packet(char* packet)
*inputparam:id
*outputparam:username,icon
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/
int construct_userinfo_packet(CHAT_CONNECT* chat_conn,char* packet)
{
    if (NULL == chat_conn|| NULL == packet)
    {
        return -1;
    }

    cJSON* userinfo = NULL;
    userinfo = cJSON_CreateObject();
    cJSON_AddNumberToObject(userinfo,STR_ID,chat_conn->id);
    cJSON_AddNumberToObject(userinfo,STR_TYPE,MESSAGE_USERINFO);    //add packet type to json
    cJSON_AddStringToObject(userinfo,STR_USERNAME,chat_conn->user_name);    //add username to json
    cJSON_AddStringToObject(userinfo,STR_ICON,chat_conn->icon);    //add icon to json
    write_log(LOG_DEBUG,"%s",cJSON_Print(userinfo)); 
    strncpy(packet,cJSON_Print(userinfo),MAXLINE); //get string from json
    write_log(LOG_DEBUG,"[%d]%s",strlen(packet),packet);
    return 0;
}

/*
*name:construct_logon_error_packet(char* packet)
*inputparam:id
*outputparam:username,icon
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/

int construct_logon_error_packet(char* packet)
{
    if (NULL == packet)
    {
        return -1;
    }
    cJSON* logon_error = NULL;
    logon_error = cJSON_CreateObject();
    cJSON_AddNumberToObject(logon_error,STR_TYPE,MESSAGE_LOGON_ERROR);    //add packet type to json
    strncpy(packet,cJSON_Print(logon_error),MAXLINE); //get string from json
    write_log(LOG_DEBUG,"[%d]%s",strlen(packet),packet);
    return 0;
}

/*
*name:packet_deal_logon
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:logon packet deal.if id and password is success return 0
*/

int packet_deal_logon(cJSON *packet,CHAT_CONNECT *chat_conn)
{
    if (NULL == packet || NULL == chat_conn)
    {
        return -1;
    }    
    /*analyze password and id*/
    char password[MAX_LEN_PASSWORD] = {0};
    cJSON *node = NULL;
    node = cJSON_GetObjectItem(packet,STR_ID);
    if (NULL == node)
    {
        //not find id
        write_log(LOG_WARNING,"not find id");
        return 1;
    }
    else
    {
        if (node->type == cJSON_Number)
        {
            chat_conn->id = node->valueint;
            write_log(LOG_DEBUG,"id:%d",chat_conn->id);
        }
    }
    node = NULL;
    node = cJSON_GetObjectItem(packet,STR_PASSWORD);
    if (NULL == node)
    {
        //not find password
        write_log(LOG_WARNING,"not find password");
        return 1;
    }
    else
    {
        if (node->type == cJSON_String)
        {
            strncpy(password,node->valuestring,MAX_LEN_PASSWORD);
        }
    }
    /*verify id and password is correct*/
    char send_packet[MAXLINE] = {0};
    if (!verify_logon_info_from_mysql(chat_conn->id,send_packet,chat_conn) && !save_user_fd_relation_to_redis(chat_conn->connect_fd,chat_conn->id))
    {
        //password and id is success and the id no have logon
        construct_userinfo_packet(chat_conn,send_packet);
    }
    else
    {
        //logon info error
        construct_logon_error_packet(send_packet);
    }
    write_log(LOG_DEBUG,"[len:%d]s->c:%s",strlen(send_packet),send_packet);
    write_data_to_socket_fd(chat_conn->connect_fd,send_packet,strlen(send_packet));


    return 0;
}

/*
*name:logout_deal  
*inputparam:CHAT_CONNECT *chat
*return: void
*describe:登出处理
*/

void logout_deal(CHAT_CONNECT *chat_conn)
{
    if (NULL == chat_conn)
    {
        write_log(LOG_WARNING,"chat_conn is null");
        return;
    }
    /*客户端登出处理*/
    //删除redis中对应的key
    if (NULL == g_redis_conn)
    {
        //未初始化redis连接
        if (-1 == init_redis_connect())
        {
            //初始化失败，直接返回错误，因为无法断定当前redis情况
            write_log(LOG_ERROR,"redis maybe is die");
            return;
        }
    }
    redisReply *reply = redisCommand(g_redis_conn, "del %d",chat_conn->id);
    write_log(LOG_INFO,"redis_cmd:[del %d]",chat_conn->id);
    //释放redis资源
    freeReplyObject(reply);
    redisFree(g_redis_conn);
}


/*
*name:chat_message_deal
*inputparam:data,data_len
*return: -1:error 0:success
*describe:消息处理
*/
int chat_message_deal(char* data,int data_len,CHAT_CONNECT *chat_conn)
{
    //从data中解析json结构
    cJSON *json = cJSON_Parse(data);
    cJSON *node = NULL;
    //cJSON_GetObjectItem 根据key来查找json节点，如果有返回非空
    node = cJSON_GetObjectItem(json,"type");
    int type = -1;
    if (NULL == node)
    {
        //get message type failed;
        write_log(LOG_ERROR,"json node type is null");
    }
    else
    {
        if (node->type == cJSON_Number)
        {
            //get message type success
            type = node->valueint;
            write_log(LOG_INFO,"type:%d",node->valueint);
        }
    }
    switch (type)
    {
    case MESSAGE_LOGON: /*登录请求*/
        packet_deal_logon(json,chat_conn);
        break;
    
    default:
        break;
    }
    return 0;

}

