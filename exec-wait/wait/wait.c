#include<stdio.h>
#include<wait.h>

int main()
{
    pid_t id = fork();
    if(id > 0)
    {
        //father
        int status = 0;
        int ret  = wait(&status);
        if(ret > 0 && (status&0x7f) == 0)
        {
            //success
            printf("child exit code:%d\n",(status>>8));
        }
        else
        {
            //signal exit
            printf("signal code:%d\n",(status>>8)&0xff);
        }
    }
    else if(id == 0)
    {
        //child
        sleep(30);
        exit(5);
    }
    else
    {
        perror("fork");
    }
    return 0;
}
