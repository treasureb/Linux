#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int SetNoBlock(int fd)
{
    int flag = fcntl(fd,F_GETFL);
    if(flag < 0){
        perror("fcntl");
        return -1;
    }

    return fcntl(fd,F_SETFL,flag | O_NONBLOCK);
}

int main()
{
    SetNoBlock(0);
    while(1){
        char buf[1024] = {0};
        printf(">");
        fflush(stdout);
        ssize_t read_size = read(0,buf,sizeof(buf) -1);
        if(read_size < 0){
            perror("read");
            sleep(1);
        } else if(read_size == 0){
            printf("read done!\n");
        }
        buf[read_size] = '\0';
        printf("-> buf:%s \n",buf);
    }
    return 0;
}
