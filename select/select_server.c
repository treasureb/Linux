#include<stdio.h>
#include<sys/select.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>

static void usage(const char *proc)
{
    printf("Usage: %s [local_ip] [local_port]\n",proc);
}

int fds[sizeof(fd_set)*8];

int startup(char *ip,int port)
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock  < 0){
        perror("socket");
        return 2;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        perror("bind");
        exit(3);
    }

    //10为底层的链接队列
    if(listen(sock,10) < 0){
        perror("bind");
        exit(4);
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
    fd_set rfds;
    int nums = sizeof(fds)/sizeof(fds[0]);
    int i = 0;
    for(;i < nums;i++){
        fds[i] = -1;
    }
    while(1){
        FD_ZERO(&rfds);
        int max = -1;
        fds[0] = listen_sock;
        struct timeval timeout = {0,0};

        for(i = 0;i < nums;i++){
            if(fds[i] > 0){
               FD_SET(fds[i],&rfds);

               if(max < fds[i]){
                   max = fds[i];
               }
            }
        }
        switch(select(max+1,&rfds,NULL,NULL,NULL)){
        case 0:
            printf("timeout...\n");
            break;
        case -1:
            perror("select");
            break;
        default:
            {
                //at least one ev ready
               for(i = 0;i < nums;i++){
                   if(fds[i] == -1){
                       continue;
                   }
                   if(i == 0 && FD_ISSET(fds[i],&rfds)){
                       struct sockaddr_in client;
                       socklen_t len = sizeof(client);
                       int new_sock = accept(fds[i],(struct sockaddr*)&client,&len);
                       if(new_sock < 0){
                           perror("accept");
                           continue;
                       }
                        printf("get client [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

                       //这里绝对不会阻塞
                           
                          int j = 1;
                          for(; j < nums;j++){
                              if(fds[j] == -1){
                                  break;
                              }
                          }
                          if(j == nums){
                              close(new_sock);
                          }else{
                              printf("fd: %d\n",new_sock);
                              fds[j] = new_sock;
                          }
                          continue;
                      }else if(i != 0 && FD_ISSET(fds[i],&rfds)){
                          char buf[2014];
                          ssize_t s = read(fds[i],buf,sizeof(buf)-1);//一次读不完，有BUG
                          if(s > 0){
                              printf("client# %s",buf);
                          }else if(s == 0){
                              printf("client is quit!\n");
                              close(fds[i]);
                              fds[i] = -1; 
                          }else{
                              perror("read");
                              close(fds[i]);
                              fds[i] = -1;
                          }
                      }else{
                           
                    }
                }//for     
            }
            break;
        }
    }
}
