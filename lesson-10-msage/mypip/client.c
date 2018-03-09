#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main()
{
    int wfd = open("myfifo",O_WRONLY);
    if(wfd < 0)
    {
        perror("open");
        exit(1);
    }

    char buf[1024] = {0};
    while(1)
    {
        printf("Please Enter:\n");
        fflush(stdout);
        ssize_t read_size = read(0,buf,sizeof(buf) - 1);
        if(read_size > 0)
        {
            buf[read_size] = 0;
            write(wfd,buf,strlen(buf));
        }
        else if(read_size <= 0)
        {
            perror("read");
            exit(1);
        }
    }
    close(wfd);
    return 0;
}
