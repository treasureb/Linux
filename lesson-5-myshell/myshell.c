#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
#include<ctype.h>
#include<ctype.h>
#include<wait.h>

char *argv[8];
int argc = 0;

void GetLoginName()
{
    struct passwd* pass;
    pass = getpwuid(getuid());
    printf("[%s@",pass->pw_name);
}

void GetHost()
{
    char name[128] = {0};
    gethostname(name,sizeof(name) - 1);
    printf("%s",name);
}

void GetDir()
{
    char pwd[128] = {0};
    getcwd(pwd,sizeof(pwd) - 1);
    int len = strlen(pwd);
    char *p = pwd + len - 1;
    while(*p != '/' && len--)
    {
        p--;
    }
    len++;
    printf("%s]#",p);
}

void Present()
{
    GetLoginName();

    GetHost();

    GetDir();
}

void Do_Parse(char *buf)
{
    int i = 0;
    int status  = 0;
    for(argc = i = 0;buf[i];++i)
    {
        if(!isspace(buf[i]) && status == 0)
        {
            argv[argc++] = buf+i;
            status = 1;
        }
        else if(isspace(buf[i]))
        {
            status = 0;
            buf[i] = 0;
        }
    }
    argv[argc] = NULL;
}

void Do_Execute()
{
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        exit(-1);
    }
    else if(id > 0)
    {
        //father
        int status;
        while(wait(&status) != id)
        {
            ;
        }
    }
    else
    {
        execvp(argv[0],argv);
    }
}
int Run()
{
    //1 GetHost
    //2 Get
    //
    char *buf[1024] = {0};
    while(1)
    {
        Present();
        fflush(stdout);
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0)
        {
            perror("read");
            return -1;
        }
        Do_Parse(buf);
        Do_Execute();
    }
}


int main()
{
    Run();
    return 0;
}
