
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 #include "write_log.h"
 
int main(int argc, char *argv[])
{
    
    
    while (1)
    {
        //创建套接字
        int sk = socket(AF_INET, SOCK_STREAM, 0);
 
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(60728);
        server.sin_addr.s_addr = inet_addr("118.31.42.38");
        //连接服务器
        while(!connect(sk, (struct sockaddr*)&server, sizeof(server)))
        {
            write_log(LOG_INFO,"update fail ,retery");
        }

        write_log(LOG_INFO,"update ip is ok");
        //关闭套接字
        close(sk);
        
        sleep(atoi(argv[1]));
    }
    
    

    return 0;
}