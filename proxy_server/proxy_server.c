#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "write_log.h"


#define LISTENQ 1024

int main(int argc,char *argv[])
{
    int listenfd = -1;
    int connfd = -1;
    socklen_t clilen;
    struct sockaddr_in servaddr,cliaddr;
    pid_t childpid = -1;
    debug_level_set(LOG_MAX);
    if (argc != 2)
    {
        write_log(LOG_ERROR,"arg error;usage:server.out port\n");
        return 0;
    }
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (-1 == listenfd)
    {
        //socket error
        write_log(LOG_ERROR,"socket error\n");
        return 0;
    }
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    write_log(LOG_DEBUG,"listen port:%d  %d",servaddr.sin_port,atoi(argv[1]));
    if (-1 == bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
    {
        write_log(LOG_ERROR,"bind error\n");
        return 0;
    }

    if (-1 == listen(listenfd,LISTENQ))
    {
        write_log(LOG_ERROR,"listen error\n");
        return 0;
    }
    int status;
    

    for ( ; ;)
    {
        clilen = sizeof(cliaddr);
        if (-1 == (connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen)))
        {
            write_log(LOG_ERROR,"accept error\n");
            return 0;
        }
        write_log(LOG_DEBUG,"connfd %d",connfd);
        struct sockaddr_storage sock_cli;
        socklen_t len = -1;

        len = sizeof(sock_cli);
        char ip[256] = {0};
        if (getpeername(connfd,(struct sockaddr*)&sock_cli,&len) < 0)
        {
            write_log(LOG_ERROR,"get client source info error");
        }
        else
        {
            struct sockaddr_in *in = (struct sockaddr_in *)&sock_cli;
            inet_ntop(AF_INET,&in->sin_addr,ip,sizeof(ip)); //ip to xxx.xxx.xxx.xxx
            write_log(LOG_DEBUG,"update ip:%s",ip);
            FILE *fp = NULL;
            fp = fopen("/var/www/html/ip/real_ip.txt", "w");
            fprintf(fp, ip);
            fclose(fp);
        }
        close(connfd);
       
    }
    close(listenfd);
    write_log(LOG_DEBUG,"the program end");
    return 0;
}



