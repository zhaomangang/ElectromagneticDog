#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include "chat.h"
int main(int argc,char *argv[])
{
    int listenfd = -1;
    int connfd = -1;
    socklen_t clilen;
    struct sockaddr_in servaddr,cliaddr;
    char buff[MAXLINE];
    pid_t childpid = -1;

    if (argc != 2)
    {
        printf("arg error;usage:server.out port\n");
        return 0;
    }
    if (-1 == (listenfd = socket(AF_INET,SOCK_STREAM,0)))
    {
        //socket error
        printf("socket error\n");
        return 0;
    }
    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (-1 == bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
    {
        printf("bind error\n");
        return 0;
    }

    if (-1 == listen(listenfd,LISTENQ))
    {
        printf("listen error\n");
        return 0;
    }

    for ( ; ;)
    {
        clilen = sizeof(cliaddr);
        if (-1 == (connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen)))
        {
            printf("accept error\n");
            return 0;
        }
        if ((childpid = fork()) < 0)
        {
            //fork error
            printf("fork error\n");
            return 0;
        }
        else if (childpid == 0)
        {
            //child
            printf("child pid %d\n",getpid());
        }
        else 
        {
            //parent
            

        }
    }

    return 0;
}

