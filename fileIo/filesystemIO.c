#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
#if 0
    umask(0);
    int fd = open("myfile",O_WRONLY|O_CREAT,0644);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }

    int count = 5;
    const char *msg = "hello world!\n";
    int len = strlen(msg);
    while(count--)
    {
        write(fd,msg,len);
    }
#endif
    close(1);
    int fd = open("myfile",O_WRONLY|O_CREAT,0666);
    if(fd < 0)
    {
        perror("open");
        return 1;
    }

//    const char *msg = "hello world!\n";
//    char buf[1024];
//    while(1)
//    {
//        ssize_t s = write(fd,buf,strlen(msg));
//        if(s > 0)
//        {
//            printf("%s",buf);
//        }
//        else
//            break;
//    }
//
    printf("fd:%d\n",fd);
    fflush(stdout);

    close(fd);
   // return 0;
   exit(0);
}
