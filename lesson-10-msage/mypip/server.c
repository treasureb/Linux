#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{

    umask(0);
    int ret = mkfifo("myfifo",0666);
    if(ret < 0)
    {
        perror("myfifo");
    }
    
    int rfd = open("myfifo",O_RDONLY);
    if(rfd == -1)
    {
        perror("open");
    }
    char buf[1024] = {0};
    while(1)
    {
        buf[0] = 0;
        printf("Please Wait...\n");
        ssize_t read_size = read(rfd,buf,sizeof(buf) - 1);
        if(read_size > 0)
        {
            buf[read_size - 1] = 0;
            printf("client say:%s\n",buf);
        }
        else if(read_size == 0)
        {
            printf("client quit,exit now\n");
            exit(0);
        }
        else
        {
            perror("read");
            exit(1);
        }
    }
    close(rfd);
    return 0;

}

