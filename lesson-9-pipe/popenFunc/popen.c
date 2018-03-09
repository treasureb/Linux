#include <stdio.h>
#include "apue.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

static pid_t *childpid = NULL;
static int maxfd;

FILE* popen(const char* cmdstring,char* type)
{
    int i;
    int fd[2];//创建匿名管道
    pid_t pid;
    FILE *fp;

    //只允许读和写
    if((type[0] != 'r' && type[0] != 'w') || type[1] != 0)//最后一个参数有误
    {
        errno = EINVAL;
        return NULL;
    }

    if(childpid == NULL)
    {
        maxfd = open_max();
        if((childpid = calloc(maxfd,sizeof(pid_t))) == NULL)//空间开辟失败
            return NULL;
    }

    if(pipe(fd) < 0)
    return NULL;//pipe函数失败
    if(fd[0] >= maxfd || fd[1] >= maxfd)//一但获取到的文件描述符超过最大的，则关闭标准输入和输出
    {
        close(fd[0]);
        close(fd[1]);
        errno = EMFILE;
        return NULL;
    }

    if((pid = fork()) < 0)
        return NULL;
   //child 
    else if(pid == 0)
    {
        if(*type == 'r')
        {
            close (fd[0]);
            if(fd[1] != STDOUT_FILENO)
            {
                dup2(fd[1],STDOUT_FILENO);
                close(fd[1]);
            }
        }
        else
        {
            close(fd[1]);
            if(fd[0] != STDIN_FILENO)
            {
                dup2(fd[0],STDIN_FILENO);
                close(fd[0]);
            }
        }

        //关闭所有文件描述符
        for(i = 0;i < maxfd;i++)
        {
            if(childpid[i] > 0)
                close(i);
        }

        execl("/bin/sh","sh","-c",cmdstring,(void*)0);
        _exit(127);
    }

    //father
    if(*type == 'r')
    {
        close(fd[1]);
        if(fp = fdopen(fd[0],type) == NULL)
            return NULL;
    }
    else
    {
        close(fd[0]);
        if(fp = fdopen(fd[1],type) == NULL)
            return NULL;
    }

    childpid[fileno(fp)] = pid;
    return fp;
}

int main()
{

    return 0;
}
