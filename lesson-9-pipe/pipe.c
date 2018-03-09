#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

void Test1()
{

    //write and read
    int fd[2] = {0};
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return 1;
    }

    printf("pipe success!\n");
    char buf[1024] = {0};
    while(1)
    {
        read(0,buf,sizeof(buf) - 1);
        ssize_t write_size  =  write(fd[1],buf,sizeof(buf) -1);
        if(write_size < 0)
        {
            perror("write");
            exit(1);
        }
    
        buf[1024] = '\0';
        ssize_t read_size = read(fd[0],buf,sizeof(buf));
        if(read_size < 0)
        {
            perror("read");
            exit(1);
        }
        else if(read_size == 0)
        {
            printf("read done!\n");
            exit(1);
        }   
        else
        {
            write(1,buf,sizeof(buf) -1);
        //    printf("read success!\n");
        }
    }
}

void Test2()
{
    //write full and not read
    int fd[2] = {0};
    int ret = pipe(fd);
   // int ret = pipe2(fd,O_NONBLOCK);
    if(ret < 0)
    {
        perror("pipe");
        exit(1);
    }

    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        exit(1);
    }
    if(id > 0)
    {
        close(fd[0]);
        char buf[655] = {0};
        memset(buf,'1',sizeof(buf));
        printf("%s",buf);
        while(1)
        {
            write(fd[1],buf,1);
        }
        close(fd[1]);
        exit(0);
    }

#if 1
    close(fd[0]);
//    char buf[1024] = {0};
//    read(fd[0],buf,10);
//    printf("%s",buf);
//    close(fd[0]);
//
#endif
}

void Test3()
{
    //only read and notwrite
    int fd[2] = {0};
    int ret= pipe(fd);
    // int ret = pipe2(fd,O_NONBLOCK);
    if(ret < 0)
    {
        perror("pipe");
        exit(1);
    }
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        exit(1);
    }
    if(id > 0)
    {
      //  close(fd[1]);
    }
    
  //  close(fd[1]);
    char buf[1024] = {0};
    memset(buf,'1',sizeof(buf));
    read(fd[0],buf,sizeof(buf)-1);
    close(fd[0]);
}

int main()
{
   // Test1();
   Test2();
   // Test3();
    return 0;
}
