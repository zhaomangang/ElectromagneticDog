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



/*
*name:get_time_now
*inputparam:void
*return: -1:deal error other:time
*describe:获取当前时间戳
*/

unsigned int get_time_now()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec;
}


/*******************************************************************************
*  func desc:   init_mysql_conn
*  input param: void
*  out   param: g_mysql_conn
*  retun value: void
********************************************************************************/
void init_mysql_conn(void** g_mysql_conn)
{
    if (NULL == g_mysql_conn)
    {
        return;
    }   
    if (NULL == *g_mysql_conn)
    {
        *g_mysql_conn = InitDbCon2(MYSQL_LOCAL, MYSQL_USER, MYSQL_PASSWD, 
            MYSQL_PORT, MYSQL_DATABASE);    
    }
    return ;
}




/*
*name:init_redis_connect
*input:void
*return: -1:faild other:success
*/

int init_redis_connect(redisContext **g_redis_conn)
{
    (*g_redis_conn) = redisConnect(CONFIG_REDIS_HOST, CONFIG_REDIS_PORT);
    if (*g_redis_conn == NULL || (*g_redis_conn)->err) {
        if (*g_redis_conn) {
            write_log(LOG_ERROR, "%s", (*g_redis_conn)->errstr);
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
        write_log(LOG_DEBUG,"pwd is ok");
        return 0;
    }
    write_log(LOG_DEBUG,"pwd is error %s %s",pwd, db_pwd);
    return 1;
}

/*
*name:get_friend_list_from_mysql
*inputparam:id
*return: -1:deal error 0:success 1:password/id error 
*describe:从数据库中加载好友列表
*/
int get_friend_list_from_mysql(int id, char* packet)
{
    if (NULL == packet)
    {
        return -1;
    }
    char sql_str[MAX_LEN_SQL_STR]={0};
    struct DbResult *dbResult = NULL;
    int ret = 0;
    char pwd[MAX_LEN_PASSWORD] = {0};
    cJSON* friend_list = NULL;
    friend_list = cJSON_CreateObject();
    cJSON_AddNumberToObject(friend_list,STR_TYPE,MESSAGE_FRIEND_LIST_RESPONSE);
    /*查询pwd*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
    }    
    snprintf(sql_str, sizeof(sql_str),SQL_SELECT_FRIEND_ALL,id);
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
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (NULL != dbResult && dbResult->nrow > 0)
        {
            int row = 0;
            for (row = 0; row < dbResult->nrow; row++)
            {
                cJSON* list = NULL;
                char tempname[LISTENQ] = {0};
                snprintf(tempname,sizeof(tempname),"%d",row);
                list = cJSON_AddObjectToObject(friend_list,tempname);
                //循环遍历select结果每一行
                if (NULL != dbResult->rows[row][0])
                {
                    //friend_id
                    cJSON_AddNumberToObject(list,STR_FRIEND_ID,atoi(dbResult->rows[row][0]));
                }
                if (NULL != dbResult->rows[row][1])
                {
                    //friend_name
                    cJSON_AddStringToObject(list,STR_FRIEND_NAME,dbResult->rows[row][1]);  
                }
                if (NULL != dbResult->rows[row][2])
                {
                    //remark
                    cJSON_AddStringToObject(list,STR_REMARK,dbResult->rows[row][2]);
                }
                if (NULL != dbResult->rows[row][3])
                {
                    cJSON_AddStringToObject(list,STR_ICON,dbResult->rows[row][3]);
                }   
            }
            cJSON_AddNumberToObject(friend_list,STR_NUM,dbResult->nrow);
            strncpy(packet,cJSON_Print(friend_list),MAXLINE); //get string from json
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        else
        {
            write_log(LOG_ERROR,"not have result by id:%d",id);
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (dbResult)
        {
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        CloseDbCon(g_mysql_conn);
        g_mysql_conn = NULL;
    }//mysqlconn

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
    char pwd[MAX_LEN_PASSWORD] = {0};

    /*查询pwd*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
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
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (NULL != dbResult && dbResult->nrow > 0)
        {
            if (NULL != dbResult->rows[0][0])
            {
                write_log(LOG_DEBUG,"userid:%d pwd from mysql is:%s",id,dbResult->rows[0][0]);
                strncpy(pwd,dbResult->rows[0][0],MAX_LEN_PASSWORD);
            } 
            else
            {
                write_log(LOG_ERROR,"not have result by id:%d",id);
                CloseDbCon(g_mysql_conn);
                g_mysql_conn = NULL;
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
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
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
    CloseDbCon(g_mysql_conn);
    g_mysql_conn = NULL;
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
    redisContext *g_redis_conn = NULL;
    //初始化redis连接
    if (-1 == init_redis_connect(&g_redis_conn))
    {
        //初始化失败，直接返回错误，因为无法断定当前redis情况
        write_log(LOG_ERROR,"redis maybe is die");
        return -1;
    }
    redisReply *reply = redisCommand(g_redis_conn, "get %d",id);
    write_log(LOG_INFO,"redis_cmd:[get %d]",id);
    if (REDIS_REPLY_NIL != reply->type)
    {
        //查到该key，证明该id当前已登录
        write_log(LOG_DEBUG,"the id %d is loging [%d]", id, reply->type);
        freeReplyObject(reply);
        redisFree(g_redis_conn);
        g_redis_conn = NULL;
        return -1;
    }
    else
    {
        //未查到，将该key插入redis
        reply = redisCommand(g_redis_conn, "set %d %d", id, fd);
        write_log(LOG_DEBUG,"set %d %d", id, fd);
        freeReplyObject(reply);
    }
    redisFree(g_redis_conn);
    g_redis_conn = NULL;
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
*name:construct_register_response(char* packet)
*inputparam:id
*outputparam:username,icon
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1

char icon[MAX_LEN_ICON] = {0};
    char user_name[MAX_LEN_USERNAME] = {0};
    char password[MAX_LEN_PASSWORD] = {0};
    char real_name[MAX_LEN_USERNAME] = {0};
    char address[MAX_LEN_ADDRESS] = {0};
    char mail[MAX_LEN_MAIL] = {0};
*/
int construct_register_response(char* packet,int u_id, char* msg)
{
    cJSON* root = NULL;
    if (NULL == packet)
    {
        return -1;
    }
    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root,STR_TYPE,MESSAGE_REGISTER_RPT);
    cJSON_AddNumberToObject(root,STR_ID,u_id);
    cJSON_AddStringToObject(root,STR_MSG,msg);    //add packet type to json
    //write_log(LOG_DEBUG,"%s",cJSON_Print(root)); 
    strncpy(packet,cJSON_Print(root),MAXLINE); //get string from json
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
    if (!verify_logon_info_from_mysql(chat_conn->id,password,chat_conn) && !save_user_fd_relation_to_redis(chat_conn->connect_fd,chat_conn->id))
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
*inputparam:id
*return: 0：not online, 在线：返回id对应的fd
*describe:判断用户是否在线
*/
int isOnLine(int id)
{
    int fd = 0;
    redisContext *g_redis_conn = NULL;
    //初始化redis连接
    if (-1 == init_redis_connect(&g_redis_conn))
    {
        //初始化失败，直接返回错误，因为无法断定当前redis情况
        write_log(LOG_ERROR,"redis maybe is die");
        return -1;
    }
    redisReply *reply = redisCommand(g_redis_conn, "get %d",id);
    write_log(LOG_INFO,"redis_cmd:[get %d]",id);
    if (REDIS_REPLY_NIL != reply->type)
    {
        //查到该key，证明该id当前已登录
        fd = atoi(reply->str);
        write_log(LOG_DEBUG,"user %d is online socket_fd = %d",id,fd);
    }
    else
    {
        write_log(LOG_DEBUG,"user %d is not online",id);
    }
    //释放redis资源
    freeReplyObject(reply);
    redisFree(g_redis_conn);
    
    return fd;
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
    if (0 == chat_conn->id)
    {
        return;
    }
    /*客户端登出处理*/
    //删除redis中对应的key
    redisContext *g_redis_conn = NULL;
    //初始化redis连接
    if (-1 == init_redis_connect(&g_redis_conn))
    {
        //初始化失败，直接返回错误，因为无法断定当前redis情况
        write_log(LOG_ERROR,"redis maybe is die");
        return -1;
    }
    redisReply *reply = redisCommand(g_redis_conn, "del %d",chat_conn->id);
    write_log(LOG_INFO,"redis_cmd:[del %d]",chat_conn->id);
    //释放redis资源
    freeReplyObject(reply);
    redisFree(g_redis_conn);
}




/*
*name:packet_deal_friend_list
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:处理好友列表获取请求
*/

int packet_deal_friend_list(cJSON *packet,CHAT_CONNECT *chat_conn)
{
    if (NULL == packet || NULL == chat_conn)
    {
        return -1;
    }
    char send_packet[MAXLINE] = {0};
    get_friend_list_from_mysql(chat_conn->id,send_packet);
    write_log(LOG_DEBUG,"%s",send_packet);
    write_data_to_socket_fd(chat_conn->connect_fd,send_packet,strlen(send_packet));

}

/*
*name:packet_deal_chat_message
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:处理转发聊天消息
*/
int packet_deal_chat_message(char* message,cJSON *packet,CHAT_CONNECT *chat_conn)
{
    if (NULL == message || NULL == packet || NULL == chat_conn)
    {
        return -1;
    }
    /*解析数据包*/
    cJSON *node = NULL;
    int send_id = -1;
    int recv_id = -1;
    char send_time[TIME_MAX_STR] = {0};
    char message_date[MAXLINE] = {0};
    node = cJSON_GetObjectItem(packet,STR_SEND_ID);
    if (NULL == node)
    {
        //未发现send_id
        write_log(LOG_WARNING,"not find send_id\n%s",message);
        return -1;
    }
    else
    {
        if (cJSON_Number == node->type)
        {
            /*又可能是其它伪装客户端消息，因此应校验发送方id是否绑定当前套接字。后期再做处理*/
            send_id = node->valueint;
            write_log(LOG_DEBUG,"send_id = %d",send_id);
        }
    }
    node = NULL;
    node = cJSON_GetObjectItem(packet,STR_RECV_ID);
    if (NULL == node)
    {
        //未发现recv_id
        write_log(LOG_WARNING,"not find recv_id\n%s",message);
        return -1;
    }
    else
    {
        if (cJSON_Number == node->type)
        {
            /**/
            recv_id = node->valueint;
            write_log(LOG_DEBUG,"recv_id = %d",recv_id);
        }
    }
    node = NULL;
    node = cJSON_GetObjectItem(packet,STR_TIME);
    if (NULL == node)
    {
        //未发现time,time只是记录发送时间，重要性较低，因此如果未发现time继续进行处理
        write_log(LOG_WARNING,"not find time\n%s",message);
    }
    else
    {
        if (cJSON_String == node->type)
        {
            /**/
            strncpy(send_time,node->valuestring,TIME_MAX_STR);
            write_log(LOG_DEBUG,"time is %s",send_time);
        }
    }
    node = NULL;
    node = cJSON_GetObjectItem(packet,STR_MESSAGE_DATA);
    if (NULL == node)
    {
        //未发现消息
        write_log(LOG_WARNING,"not find message\n%s",message);
        return -1;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            /**/
            strncpy(message_date,node->valuestring,MAXLINE);
            write_log(LOG_DEBUG,"message is %s",message_date);
        }
    }
    /*解析完成，根据接收方是否在线决定直接发送还是存入数据库*/
    int recv_fd = isOnLine(recv_id);
    write_log(LOG_DEBUG,"is online %d packet string:%s",recv_fd,message);
    if (recv_fd)
    {
        //接收方在线
        write_data_to_socket_fd(recv_fd,message,strlen(message));
    }
    else
    {
        //不在线
    }
}

/*
*name:create_verify_code
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:处理转发聊天消息
*/
int create_verify_code()
{
    return get_time_now() % 1000;
}


/*
*name:generate_user_id
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:处理转发聊天消息
*/
int generate_user_id()
{
    char sql_str[MAX_LEN_SQL_STR]={0};
    struct DbResult *dbResult = NULL;
    int ret = 0;
    int uid = -1;
    /*查询max_id*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
    }
    snprintf(sql_str, sizeof(sql_str),SQL_SELECT_MAX_ID);
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
            write_log(LOG_ERROR,"not find max id");
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (NULL != dbResult && dbResult->nrow > 0)
        {
            if (NULL != dbResult->rows[0][0])
            {
                write_log(LOG_DEBUG,"maxid = %s",dbResult->rows[0][0]);
                uid = atoi(dbResult->rows[0][0]);
            } 
            else
            {
                write_log(LOG_ERROR,"not have result by id:%d");
                CloseDbCon(g_mysql_conn);
                g_mysql_conn = NULL;
                return -1;
            }
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
        else
        {
            write_log(LOG_ERROR,"not have result by id:%d");
            CloseDbCon(g_mysql_conn);
            g_mysql_conn = NULL;
            return -1;
        }
        if (dbResult)
        {
            FreeDbResult(dbResult);
            dbResult = NULL; 
        }
    }//mysqlconn
    uid += 3;
    CloseDbCon(g_mysql_conn);
    g_mysql_conn = NULL;
    return uid;
}

/*
*name:packet_deal_chat_message
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:处理转发聊天消息
*/
int packet_deal_register_verify_code(cJSON *packet,CHAT_CONNECT *chat_conn)
{
    if (NULL == packet || NULL == chat_conn)
    {
        return -1;
    }
    /*解析数据包*/
    cJSON *node = NULL;
    char email[MAXLINE] = {0};

    node = cJSON_GetObjectItem(packet,STR_MAIL);
    if (NULL == node)
    {
        //未发现send_id
        write_log(LOG_WARNING,"not find email");
        return -1;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(email,node->valuestring,sizeof(email));
            write_log(LOG_DEBUG,"email = %s",email);
        }
    }
    /*解析完成，生成验证码*/
    chat_conn->verify_code = create_verify_code();

    char cmd_str[MAXLINE] = {0};
    /*调用python 脚本发送给用户*/
    snprintf(cmd_str, sizeof(cmd_str),EMAIL_SEND_CMD,email,chat_conn->verify_code);
    write_log(LOG_DEBUG,"EMAIL_SEND:%s",cmd_str);
    system(cmd_str);

}

/*
*name:packet_deal_register_message
*inputparam:packet
*return: -1:deal error 0:success 1:password/id error 
*describe:注册请求处理
*/

int packet_deal_register_message(cJSON *packet,CHAT_CONNECT *chat_conn)
{
    int ret = -1;
    int uid = -1;
    char send_packet[MAXLINE] = {0};
    char cmd_str[MAXLINE] = {0};
    if (NULL == packet || NULL == chat_conn)    
    {
        construct_register_response(send_packet,-1,"注册失败-未知错误");
        goto RET_FLAG;
    }
    /*解析数据包*/
    cJSON *node = NULL;
    char icon[MAX_LEN_ICON] = {0};
    char user_name[MAX_LEN_USERNAME] = {0};
    char password[MAX_LEN_PASSWORD] = {0};
    char real_name[MAX_LEN_USERNAME] = {0};
    char address[MAX_LEN_ADDRESS] = {0};
    char mail[MAX_LEN_MAIL] = {0};
    int verify_code = 0;

    node = cJSON_GetObjectItem(packet,STR_ICON);
    if (NULL == node)
    {
        //未发现icon
        write_log(LOG_WARNING,"not find ICON");
        construct_register_response(send_packet,uid,"注册失败-未知错误");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(icon,node->valuestring,sizeof(icon));
            write_log(LOG_DEBUG,"email = %s",icon);
        }
    }
    
    /*verify_code*/
    node = cJSON_GetObjectItem(packet,STR_VERIFY_CODE);
    if (NULL == node)
    {
        //verify_code
        write_log(LOG_WARNING,"not find verify_code");
        construct_register_response(send_packet,uid,"注册失败-未知错误");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_Number == node->type)
        {
            verify_code = node->valueint;
            write_log(LOG_DEBUG,"verify code = %d",verify_code);
        }
    }
    /*校验验证码*/
    if (verify_code != chat_conn->verify_code)
    {
        /*验证码错误*/
        construct_register_response(send_packet,uid,"注册失败-验证码错误");
        goto RET_FLAG;
    }

    /*user_name*/
    node = cJSON_GetObjectItem(packet,STR_USERNAME);
    if (NULL == node)
    {
        //未发现user_name
        write_log(LOG_WARNING,"not find user_name");
        construct_register_response(send_packet,uid,"注册失败-未知错误");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(user_name,node->valuestring,sizeof(user_name));
            write_log(LOG_DEBUG,"user_name = %s",user_name);
        }
    }
    /*pwd*/
    node = cJSON_GetObjectItem(packet,STR_PASSWORD);
    if (NULL == node)
    {
        //未发现PWD
        write_log(LOG_WARNING,"not find pwd");
        construct_register_response(send_packet,uid,"注册失败-未知错误");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(password,node->valuestring,sizeof(password));
            write_log(LOG_DEBUG,"password = %s",password);
        }
    }

    /*real_name*/
    node = cJSON_GetObjectItem(packet,STR_REAL_NAME);
    if (NULL == node)
    {
        //未发现PWD
        write_log(LOG_WARNING,"not find real_name");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(real_name,node->valuestring,sizeof(real_name));
            write_log(LOG_DEBUG,"real_name = %s",real_name);
        }
    }

    /*address*/
    node = cJSON_GetObjectItem(packet,STR_ADDRESS);
    if (NULL == node)
    {
        //未发现address
        write_log(LOG_WARNING,"not find address");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(address,node->valuestring,sizeof(address));
            write_log(LOG_DEBUG,"real_name = %s",address);
        }
    }

    /*mail*/
    node = cJSON_GetObjectItem(packet,STR_MAIL);
    if (NULL == node)
    {
        //mail
        write_log(LOG_WARNING,"not find mail");
        goto RET_FLAG;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            strncpy(mail,node->valuestring,sizeof(mail));
            write_log(LOG_DEBUG,"mail = %s",mail);
        }
    }
    /*生成id*/
    uid = generate_user_id();
    if (-1 == uid)
    {
        write_log(LOG_ERROR,"generate uid fail");
        construct_register_response(send_packet,uid,"注册失败");
        goto RET_FLAG;
    }
    save_user_info_to_mysql(uid,icon,user_name,password,real_name,address,mail);
    construct_register_response(send_packet,uid,"注册成功");
    
    

RET_FLAG:
    write_log(LOG_DEBUG,"send");
    write_data_to_socket_fd(chat_conn->connect_fd,send_packet,strlen(send_packet));
    /*调用python 脚本发送给用户*/
    snprintf(cmd_str, sizeof(cmd_str),EMAIL_SEND_UID,mail,uid);
    write_log(LOG_DEBUG,"EMAIL_SEND:%s",cmd_str);
    system(cmd_str);
    return ret;
}

/*
*name:save_sort_histort_to_mysql
*inputparam:id,sort_text,time
*return: -1:deal error 0:success 
*describe:将搜索内容保存至mysql
*/

int save_sort_histort_to_mysql(int id, char* sort_text, unsigned int time_now)
{
    if (NULL == sort_text)
    {
        return -1;
    }
    char sql_str[MAX_LEN_SQL_STR]={0};
    int ret = -1;
    /*插入mysql*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
    }
    snprintf(sql_str, sizeof(sql_str),SQL_INSERT_MUSIC_SORT,id,sort_text,time_now);
    write_log(LOG_DEBUG,"%s",sql_str);
    if (NULL != g_mysql_conn)
    {
        //insert
        ret = db_ExecSql(g_mysql_conn,sql_str);
        write_log(LOG_DEBUG,"g not null %d",ret);
        
    }//mysqlconn
    CloseDbCon(g_mysql_conn);
    g_mysql_conn = NULL;
    return ret;
}

/*
*name:save_user_info_to_mysql
*inputparam:id,sort_text,time
*return: -1:deal error 0:success 
*describe:将搜索内容保存至mysql
 char icon[MAX_LEN_ICON] = {0};
    char user_name[MAX_LEN_USERNAME] = {0};
    char password[MAX_LEN_PASSWORD] = {0};
    char real_name[MAX_LEN_USERNAME] = {0};
    char address[MAX_LEN_ADDRESS] = {0};
    char mail[MAX_LEN_MAIL] = {0};
*/

int save_user_info_to_mysql(int u_id, char* icon, char* user_name,char* pwd, char* real_name, char* address, char* mail)
{
    char sql_str[MAX_LEN_SQL_STR]={0};
    int ret = -1;
    /*插入mysql*/
    void *g_mysql_conn = NULL;
    init_mysql_conn(&g_mysql_conn);
    if(NULL == g_mysql_conn)
    {
        write_log(LOG_ERROR,"connect mysql error");
        return -1;
    }
    //`user_id`,`user_name`,`real_name`,`address`,`pwd`,`email`,`icon`,`register_time`
    write_log(LOG_DEBUG,"time:%ld",get_time_now());
    //                                                      %d, '%s',     '%s',     '%s',  '%s','%s','%s',%ld
    snprintf(sql_str, sizeof(sql_str),SQL_INSERT_USER_INFO,u_id,user_name,real_name,address,pwd,mail,icon,get_time_now());
    write_log(LOG_DEBUG,"%s",sql_str);
    if (NULL != g_mysql_conn)
    {
        //insert
        ret = db_ExecSql(g_mysql_conn,sql_str);
        write_log(LOG_DEBUG,"g not null %d",ret);
        
    }//mysqlconn
    CloseDbCon(g_mysql_conn);
    g_mysql_conn = NULL;
    return ret;
}

/*
*name:packet_deal_music_sort_message
*inputparam:packet
*return: -1:deal error 0:success
*describe:处理音乐搜索数据
*/
int packet_deal_music_sort_message(cJSON *packet,CHAT_CONNECT *chat_conn)
{
    if (NULL == packet || NULL == chat_conn)
    {
        write_log(LOG_ERROR,"param is null");
        return -1;
    }
    /*解析json*/
    cJSON *node = NULL;
    int id = 0;
    char sort_text[MAX_SORT_TEXT] = {0};
    node = cJSON_GetObjectItem(packet,STR_ID);
    if (NULL == node)
    {
        //未发现id
        write_log(LOG_WARNING,"not find id");
        return -1;
    }
    else
    {
        if (cJSON_Number == node->type)
        {
            /*又可能是其它伪装客户端消息，因此应校验发送方id是否绑定当前套接字。后期再做处理*/
            id = node->valueint;
            write_log(LOG_DEBUG,"send_id = %d",id);
        }
    }
    node = NULL;
    node = cJSON_GetObjectItem(packet,STR_SORT_TEXT);
    if (NULL == node)
    {
        //未发现sort_text
        write_log(LOG_WARNING,"not find sort_text");
        return -1;
    }
    else
    {
        if (cJSON_String == node->type)
        {
            /**/
            strncpy(sort_text,node->valuestring,MAX_SORT_TEXT);
            write_log(LOG_DEBUG,"SORT_TEXT is %s",sort_text);
        }
    }
    return save_sort_histort_to_mysql(id,sort_text,get_time_now());
}



/*
*name:chat_message_deal
*inputparam:data,data_len
*return: -1:error 0:success
*describe:消息处理
*/
int chat_message_deal(char* data,int data_len,CHAT_CONNECT *chat_conn)
{
    if (NULL == data || 0 == data_len)
    {
        return 0;
    }
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
    case MESSAGE_FRIEND_LIST:   /*好友列表请求*/
        packet_deal_friend_list(json,chat_conn);
        break;
    case MESSAGE_CHAT_DATE:     /*聊天消息*/
        packet_deal_chat_message(data,json,chat_conn);
        break;
    case MESSAGE_VERIFY_REQ:    /*注册验证码请求*/
        packet_deal_register_verify_code(json,chat_conn);
        break;
    case MESSAGE_REGISTER_REQ:  /*注册请求*/
        packet_deal_register_message(json,chat_conn);
        break;
    case MESSAGE_MUSIC_SORT: /*音乐搜索*/
        packet_deal_music_sort_message(json,chat_conn);
    default:
        break;
    }
    return 0;

}

