#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd;
    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";
    if((fd=creat("file.hole",0644)) < 0)
        perror("creat");
    if(write(fd,buf1,10) != 10)
        perror("buf1 write error");
    if(lseek(fd,20,SEEK_SET) == -1)
        perror("lseek");
    if(write(fd,buf2,10) != 10)
        perror("buf2 write error");
    exit(0);
}
