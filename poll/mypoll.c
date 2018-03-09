#include<poll.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>


int main()
{
    struct pollfd fds;
    fds.fd = 0;
    fds.events = POLLIN;
    fds.revents = 0;
    int timeout = -1;
    while(1){
        switch(poll(&fds,1,timeout)){
        case 0:
            printf("timeout...");
            break;
        case -1:
            perror("poll");
            break;
        default:
            {
                char buf[1024];
                //at least one ev ready!!!
                if(fds.revents & POLLIN){
                    ssize_t s = read(fds.fd,buf,sizeof(buf));
                    if(s > 0){
                        buf[s] = 0;
                        printf("echo# %s\n",buf);
                    }
                }
            }
            break;
        }
    }
}
