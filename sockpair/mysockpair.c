#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
    int sv[2];
    if(socketpair(PF_LOCAL,SOCK_STREAM,0,sv) < 0){
        perror("socketpair");
    } 
    pid_t id = fork();
    if(id < 0){
        perror("fork");
    }else if(id ==0){//child
        close(sv[0]);
        char buf[1024];
        while(1){
            ssize_t s = read(sv[1],buf,sizeof(buf)-1);
            if(s > 0){
                buf[s] = 0;
                printf("father say to client:# %s\n",buf);
            }
            char *msg = "I am your child!\n";
            write(sv[1],msg,strlen(msg));
            sleep(1);
        }
    }else{
        close(sv[1]);
        const char *msg = "I am your father";
        char buf[1024];
        while(1){
            write(sv[0],msg,strlen(msg));
            ssize_t s = read(sv[0],buf,sizeof(buf)-1);
            if(s > 0){
                buf[s] = 0;
                printf("child sat to father: %s\n",buf);
            }
        }
    } 
}
