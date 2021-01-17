#include "chat.h"
#include "cJSON.h"
#include "write_log.h"
#include "message_type.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>

void demo_json(char *data)
{
    //从data中解析json结构
    cJSON *json = cJSON_Parse(data);
    cJSON *node = NULL;

    //cJSON_GetObjectItem 根据key来查找json节点，如果有返回非空
    node = cJSON_GetObjectItem(json,"id");
    if (NULL == node)
    {
        write_log(LOG_WARNING,"json node id is null");
    }
    else
    {
        if (node->type == cJSON_Number)
        {
            write_log(LOG_INFO,"id:%d",node->valueint);
        }
    }
}


/*
*name:verify_logon_info_from_mysql
*inputparam:id,password
*return: -1:deal error 0:success 1:password/id error 
*describe:logon info verify
*/

int verify_logon_info_from_mysql(int id,char* password)
{
    if (id <= 0 || NULL == password)
    {
        return -1;
    }
    if (id == 100001 && strcmp(password,"Z001221z"))
    {
        return 0;
    }

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



    return 0;
}


/*
*name:get_user_info_from_mysql
*inputparam:id
*outputparam:username,icon
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/

int get_user_info_from_mysql(int id,char* username,char* icon)
{
    if (NULL == username || NULL == icon)
    {
        return -1;
    }

    strncpy(username,"mason",MAX_LEN_USERNAME);
    strncpy(icon,"1",MAX_LEN_ICON);
    return 0;
}


/*
*name:construct_userinfo_packet(char* packet)
*inputparam:id
*outputparam:username,icon
*return: -1:deal error other:send bit nums 
*describe:write to fd,if write success return bit nums.else return -1
*/
int construct_userinfo_packet(int id,char* packet)
{
    if (NULL == packet)
    {
        return -1;
    }
    char username[MAX_LEN_USERNAME] = {0};
    char icon[MAX_LEN_ICON] = {0};
    
    if (get_user_info_from_mysql(id,username,icon))
    {
        write_log(LOG_WARNING,"get user info error");
    }
    cJSON* userinfo = NULL;
    userinfo = cJSON_CreateObject();
    cJSON_AddNumberToObject(userinfo,STR_ID,id);
    cJSON_AddNumberToObject(userinfo,STR_TYPE,MESSAGE_USERINFO);    //add packet type to json
    cJSON_AddStringToObject(userinfo,STR_USERNAME,username);    //add username to json
    cJSON_AddStringToObject(userinfo,STR_ICON,icon);    //add icon to json
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
    cJSON_AddNumberToObject(userinfo,STR_TYPE,MESSAGE_LOGON_ERROR);    //add packet type to json
    strncpy(packet,cJSON_Print(userinfo),MAXLINE); //get string from json
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
    char packet[MAXLINE] = {0};
    if (!verify_logon_info_from_mysql(chat_conn->id,password) && !save_user_fd_relation_to_redis(chat_conn->connect_fd,chat_conn->id))
    {
        //password and id is success and the id no have logon
        construct_userinfo_packet(chat_conn->id,packet);
    }
    else
    {
        //logon info error
        construct_logon_error_packet(packet);
    }
    write_log(LOG_DEBUG,"[len:%d]s->c:%s",strlen(packet),packet);
    write_data_to_socket_fd(chat_conn->connect_fd,packet,strlen(packet));
    return 0;
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

