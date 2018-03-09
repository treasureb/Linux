#include <sys/wait.h> 
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int My_signal(const char* cmdstring)//获取一个命令行
{
    pid_t pid;
    int status;//保存退出码的信息
    struct sigaction ignore,saveintr,savequit;
    sigset_t chldmask,savemask;

    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if(sigaction(SIGINT,&ignore,&saveintr) < 0)
        return -1;
    if(sigaction(SIGQUIT,&ignore,&savequit) < 0)
        return -1;

    sigemptyset(&chldmask);
    sigaddset(&chldmask,SIGCHLD);
    if(sigprocmask(SIG_BLOCK,&chldmask,&savemask) < 0)
        return -1;

    if((pid = fork()) < 0)
    {
        status = 0;
    }
    else if( pid == 0)
    {
        sigaction(SIGINT,&saveintr,NULL);
        sigaction(SIGQUIT,&savequit,NULL);
        sigprocmask(SIG_SETMASK,&savemask,NULL);

        execl("/bin/sh","sh","-c",cmdstring,(char*)0);
        _exit(127);
    }
    else
    {
        while(waitpid(pid,&status,0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }


    if(sigaction(SIGINT,&saveintr,NULL) < 0)
        return -1;
    if(sigaction(SIGQUIT,&savequit,NULL) < 0)
        return -1;
    if(sigprocmask(SIG_SETMASK,&savemask,NULL) < 0)
        return -1;

    return status;
}

int main()
{
    My_signal("date > file");
    return 0;
}
