#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("Usage ./server [ip] [port]\n");
        return 1;
    }

    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("sock");
        return 2;
    }

    struct sockaddr_in local; 
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(argv[1]);
    local.sin_port = htons(atoi(argv[2]));

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        perror("bind");
        return 3;
    }

    printf("listen before\n");
    //第二个参数为等待队列的长度
    int ret = listen(sock,10);
    printf("listen after\n");
    if(ret < 0){
        perror("listen");
        return 4;
    }

    while(1){
        struct sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        int newsock = accept(sock,(struct sockaddr*)&peer_addr,&len);
        if(newsock < 0){
            perror("accept");
            continue;
        }
        while(1){
            char buf[1024] = {0};
            ssize_t read_size = read(newsock,buf,sizeof(buf)-1);
            if(read_size < 0){
                perror("read");
                close(newsock);
                continue;
            }
            if(read_size == 0){
                printf("client close\n");
                close(newsock);
                break;
            }
            buf[read_size] = '\0';
            printf("[%s : %d] %s\n",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port),buf);
            
            write(newsock,buf,strlen(buf));
       }
   }

    close(sock);
    return 0;
}
