/*
 *filename:chat.h
 *time:2020/12/27
 *author:MasonZhao
 *email:zhaomangang@qq.com
 */

#ifndef _CHAT_
#define _CHAT_


#define LISTENQ 1024

#define MAXLINE 4096
#define BUFFSIZE 8192

#define RESOURCE_IP_MAX 32



typedef struct _CHAT_CONNECT_ {
    int connect_fd; //client connect socket fd
    unsigned int source_port;   //源端口号
    char source_ip[RESOURCE_IP_MAX];  //源ip
    //...

}CHAT_CONNECT;

extern void demo_json(char* data);


#endif
