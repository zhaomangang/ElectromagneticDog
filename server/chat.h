/*
 *filename:chat.h
 *time:2020/12/27
 *author:MasonZhao
 *email:zhaomangang@qq.com
 */

#ifndef _CHAT_
#define _CHAT_

#include "message_type.h"

#define LISTENQ 1024

#define MAXLINE 4096

#define RESOURCE_IP_MAX 32
#define MAX_LEN_PWD 256


#define CONFIG_REDIS_HOST   "127.0.0.1"
#define CONFIG_REDIS_PORT   6379

/************************mysql macro********************************************/
#define MYSQL_LOCAL                 "127.0.0.1"
#define MYSQL_USER                   "root"
#define MYSQL_PASSWD              "Z001221z."
#define MYSQL_DATABASE           "elec_dog" 
#define JUMP_MYSQL_PORT        3306

#define MAX_LEN_SQL_STR 1024

#define SQL_SELECT_USERINFO_BY_ID   "SELECT `pwd`,`user_name`,`icon` FROM `elec_dog`.`user_info` WHERE `user_id` = %d"

typedef struct _CHAT_CONNECT_ {
    int connect_fd; //client connect socket fd
    unsigned int source_port;   //源端口号
    char source_ip[RESOURCE_IP_MAX];  //源ip
    int id; //user id
    char user_name[MAX_LEN_USERNAME];   //用户名
    char icon[MAX_LEN_ICON];    //icon
    //...
}CHAT_CONNECT;

//
int chat_message_deal(char* data,int data_len,CHAT_CONNECT *chat_conn);
void logout_deal(CHAT_CONNECT *chat_conn);


#endif
