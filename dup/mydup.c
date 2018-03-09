#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
    umask(0);
    int fd = open("./log",O_WRONLY|O_CREAT,0666);
    if(fd < 0){
        perror("open");
        return 1;
    }

    //int dup(oldfd,newfd)
    fd = dup2(fd,1);
//    close(1);
//    fd = dup(fd);
    const char *msg = "hello,world";
    int count = 0;
    while(count++ < 10){
        printf("%s %d %d\n",msg,count,fd);
        fflush(stdout);
//        write(fd,msg,strlen(msg));
    }
    close(fd);
    return 0;
}
