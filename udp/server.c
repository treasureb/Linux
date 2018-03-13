/*
 * 一个服务器程序的典型逻辑
 * 1.初始化(指定IP地址和端口号，加载需要的数据文件)
 * 2.进入事见循环(进入一个死循环，无限的等待客户端的请求)
 *  a.)读取客户端发送的数据
 *  b.)根据客户端发送的数据，进行计算(对于不同用途的服务器，计算的具体逻辑各不相同)
 *  c.)根据计算出来的最终结果，拼接相应的字符串  
 */

/*
 * 如何确定一个唯一的通信
 * 1.源IP
 * 2.目的IP
 * 3.源端口号
 * 4.目的端口号
 * 5.协议类型
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("Usage ./server [ip] [port]\n");
        return 1;
    }

    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        perror("socket");
        return 2;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(argv[1]);//字符转换为IP地址
    local.sin_port = htons(atoi(argv[2]));//先将字符串转为数字，然后转换字节序
    
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        perror("bind");
        return 3;
    }

    while(1){
        struct sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        char buf[1024] = {0};
        ssize_t read_size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer_addr,&len);
        if(read_size < 0){
            perror("recvfrom");
            continue;
        }
        buf[read_size] = '\0';
        //将地址转化为字符串输出，
        printf("[%s:%d] %s\n",inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port),buf);


        //服务器响应
        sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer_addr,sizeof(peer_addr));
    }
    return 0;
}
