#include<stdio.h>
#include<sys/select.h>
#include<unistd.h>

int main()
{
    while(1){
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0,&fds);
        int ret = select(1,&fds,NULL,NULL,NULL);
        if(ret < 0){
            perror("select");
            return 1;
        }
        if(ret== 0){
            printf("select timeout\n");
            continue;
        }
        char buf[1024] = {0};
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0){
            perror("read");
            return 2;
        }else if(read_size == 0){
            printf("read done!\n");
        }
        
        buf[read_size] = '0';
        printf("%s\n",buf);
    }
    return 0;
}
