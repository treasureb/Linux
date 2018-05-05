#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd;
    char buf[256];
    fd = creat("hello.txt",0644);
    write(fd,"hello world!\n",13);
    close(fd);
}
