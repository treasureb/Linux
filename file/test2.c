#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd;
    char buf[256];
    fd = open("hello.txt",O_WRONLY);
    write(fd,"this is second line!\n",21);
    close(fd);
}
