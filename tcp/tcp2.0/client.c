#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("Usage ./client [ip] [port]\n");
        return 1;
    }
    
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        perror("socket");
        return 2;
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    socklen_t len = sizeof(server_addr);
    //不需要bind，启动后由操作系统分配一个端口号
    
    int ret = connect(sock,(struct sockaddr*)&server_addr,len);
    if(ret < 0){
        perror("connetc");
        return 3;
    }

    while(1){
        char buf[1024] = {0};
        printf("> ");
        fflush(stdout);
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0){
            perror("read");
            return 1;
        }
        buf[read_size] = '\0';

        ssize_t write_size = write(sock,buf,strlen(buf));
        if(write_size < 0){
            perror("sendto");
            return 2;
        }
        
        char buf_recv[1024]  = {0};
        read_size = read(sock,buf_recv,sizeof(buf_recv));
        if(read_size < 0){
            perror("recv");
            return 3;
        }

        buf_recv[read_size] = '\0';
        printf("[%s:%d] %s\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port),buf_recv);

    }
    return 0;
}
