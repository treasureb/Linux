#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
    int fd1,fd2,read_size;
    char buf[512];
    if(argc <= 2){
        printf("you forgot the enter the filename\n");
        exit(1);
    }
    fd1 = open(argv[1],O_RDONLY,0644);
    fd2 = creat(argv[2],0644);
    while((read_size = read(fd1,buf,512)) > 0){
        write(fd2,buf,read_size);
    }
    close(fd1);
    close(fd2);
}
