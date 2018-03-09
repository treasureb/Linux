#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define SIZE 1024

const char* msg = "HTTP/1.0 200 OK\r\n\r\n<html><h1>hello epoll!</h1></html>\r\n";

static void usage(const char *proc)
{
    printf("Usage: %s [local_ip] [local_port]\n",proc);
}

int startup(const char* ip,int port)
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket");
        exit(3);
    }

    //地址重用
    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);
    socklen_t len = sizeof(local);
    if(bind(sock,(struct sockaddr*)&local,len) < 0){
        perror("bind");
        exit(4);
    }

    if(listen(sock,10) < 0){
        perror("listen");
        exit(5);
    }
    return sock;
}

int main(int argc,char *argv[])
{
    if(argc != 3){
        usage(argv[0]);
        return 1;
    }

    int listen_sock = startup(argv[1],atoi(argv[2]));
    int epfd = epoll_create(256);
    if(epfd < 0){
        perror("epoll_create");
        return 2;
    }

    printf("sock: %d,epfd: %d\n",listen_sock,epfd);
    

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;

    epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev);

    int num = 0;
    int timeout = -1;
    struct epoll_event revs[SIZE];
    while(1){
        switch((num = epoll_wait(epfd,revs,SIZE,timeout))){
            case -1:
                perror("epoll_wait");
                break;
            case 0:
                printf("timewait...\n");
                break;
            default:
                {
                    //at least one ev ready!
                    int i = 0;
                    for(;i < num;i++){
                        int fd = revs[i].data.fd;
                        if(fd == listen_sock && (revs[i].events & EPOLLIN)){
                            //listen sock ready!
                            struct sockaddr_in client;
                            socklen_t len = sizeof(client);
                            int rw_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
                            if(rw_sock < 0){
                                perror("accept");
                                continue;
                            }
                            printf("get a new clinet [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

                            ev.events = EPOLLIN;
                            ev.data.fd = rw_sock;
                            epoll_ctl(epfd,EPOLL_CTL_ADD,rw_sock,&ev);
                        }else if(fd != listen_sock){
                            if(revs[i].events & EPOLLIN){
                                //normal sock read ev ready!
                                char buf[SIZE];
                                ssize_t s = read(fd,buf,sizeof(buf)-1);
                                if(s > 0){
                                    buf[s] = 0;
                                    printf("client say# %s\n",buf);
                                    ev.events = EPOLLOUT;
                                    ev.data.fd = fd;
                                    epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
                                }else if(s == 0){
                                    printf("client is quit\n");
                                    close(fd);
                                    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                                }else{
                                    perror("read");
                                    close(fd);
                                    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                                }
                            }else if(revs[i].events & EPOLLOUT){
                                //normal sock write ev ready!
                                write(fd,msg,strlen(msg));
                                close(fd);
                                epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                            }else{
                                //other ev
                            }
                        }else{
                            //other
                        }
                    }
                }
                break;
        }
    }
    close(listen_sock);
    close(epfd);
    return 0;
}
