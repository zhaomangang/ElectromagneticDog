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
#include "chat.h"
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
        if ((childpid = fork()) < 0)
        {
            //fork error
            write_log(LOG_ERROR,"fork error\n");
            return 0;
        }
        else if (childpid == 0)
        {
            //child
            write_log(LOG_DEBUG,"child pid %d\n",getpid());
           if (-1 == close(listenfd))
           {
                //子进程关闭监听套接字失败
                write_log(LOG_ERROR,"child close listen fail,pid is %d",getpid());
                exit(0);
           }
           connect_deal(connfd);    //子进程处理函数
           exit(0);

        }
        else 
        {
            //parent
            // if (-1 == close(connfd))
            // {
            //     write_log(LOG_ERROR,"parent close connect fd fail");
            // }
        //    if (wait(&status) != childpid)
        //     {
        //        write_log(LOG_ERROR,"error %d",status);
        //     }
    
        }
    }
    write_log(LOG_DEBUG,"the program end");
    return 0;
}

/*
 *name:connect_deal
 *input pramer: connect_fd
 *output pramer: 
 *return:void
 *decribe:客户端处理函数
 * */
void connect_deal(int connect_fd)
{
    ssize_t n;
    char buff[MAXLINE] = {0};
    CHAT_CONNECT* chat_conn = NULL;
    chat_conn = malloc(sizeof(CHAT_CONNECT));
    if (NULL == chat_conn)
    {
       //malloc error 
       write_log(LOG_ERROR,"malloc error");
       chat_conn = NULL;
       return;
    }
    chat_conn->connect_fd = connect_fd;
    struct sockaddr_storage sock_cli;
    socklen_t len = -1;

    len = sizeof(sock_cli);

    if (getpeername(connect_fd,(struct sockaddr*)&sock_cli,&len) < 0)
    {
        write_log(LOG_ERROR,"get client source info error");
    }
    else
    {
        struct sockaddr_in *in = (struct sockaddr_in *)&sock_cli;
        inet_ntop(AF_INET,&in->sin_addr,chat_conn->source_ip,sizeof(chat_conn->source_ip)); //ip to xxx.xxx.xxx.xxx
        chat_conn->source_port = htons(in->sin_port);
        write_log(LOG_DEBUG,"source ip:%s",chat_conn->source_ip);
        write_log(LOG_DEBUG,"source port:%d",chat_conn->source_port);
    }
    
    while (1)
    {
        n = read(connect_fd,buff,MAXLINE-2);
        if (n == 0)
        {
            //close connect by cient
            
            write_log(LOG_INFO,"close by client");
            if (-1 == close(connect_fd))
            {
                //close connect_fd fail;
                write_log(LOG_ERROR,"close connect fail,child pid is %d",getpid());
            }
            logout_deal(chat_conn);
            break;  //end child'
        }
        else if (n > 0)
        {
            //recv data success ,n bit data;
            buff[n+1] = '\0';
            write_log(LOG_DEBUG,"recv data:%s",buff);
            if (-1 == chat_message_deal(buff,n,chat_conn))
            {
                
            }
        }
        else 
        {
            //other error;
            write_log(LOG_ERROR,"recv other error in child %d",getpid());
            if (-1 == close(connect_fd))
            {
                write_log(LOG_ERROR,"close connect_fd fail,childpid is %d",getpid());
            }
            logout_deal(chat_conn);
            break;
        }
    }//while
}//dealconnect




