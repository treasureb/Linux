#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd,read_size;
    char buf[256];
    fd = open("hello.txt",O_RDONLY);
    while((read_size = read(fd,buf,256)) > 0){
        write(2,buf,read_size);
    }
    close(fd);
    return 0;
}
