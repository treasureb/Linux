#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
    pid_t id = fork();
    if(id > 0)
    {
        //father
        int status = 0;
        pid_t ret = 0;
        do
        {
            ret = waitpid(-1,&status,WNOHANG);//no-blocking
            if(ret == 0)
            {
                printf("child is running\n");
            }
            sleep(1);
        }
        while(ret == 0);
        
        if(WIFEXITED(status) && ret == id)
        {
            printf("wait child 3s success,child return code is:%d\n",WEXITSTATUS(status));
        }
        else
        {
            printf("wait child failed,return\n");
            return 1;
        }

    }
    else if(id == 0)
    {
        //child
        printf("child is run ,pid is:%d\n",getpid());
        sleep(3);
        exit(1);
    }
    else
    {
        printf("%s fork error\n",__FUNCTION__);
        return 1;
    }
    return 0;
}
