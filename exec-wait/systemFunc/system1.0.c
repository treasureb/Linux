#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int My_System(const char* cmdstring)
{
    pid_t pid;
    int status;

    if(cmdstring == NULL)//输如的命令行参数有误
    {
        return 1;
    }

    if((pid = fork()) < 0)//进程创建失败
    {
        status = -1;
    }
    else if( pid == 0 )//如果是子进程就执行程序替换
    {
        //这里是直接使用shell来执行命令行参数，如果自己实现
        execl("/bin/sh","sh","-c",cmdstring,(char*)0);
        _exit(127);//内核中就返回覅错误码，保持一致嘛,至于为什么不调用exit，防止子进程继承了父进程缓冲区的的一些数据
    }
    else
    {
        while(waitpid(pid,&status,0) < 0)
        {
            if(errno != EINTR)//EINTR为早期的UNIX中的错误类型值
            {
                status = -1;
                break;
            }
        }
    }
    return status;
}

int main() 
{
    My_System("date > file");
    return 0;
}
