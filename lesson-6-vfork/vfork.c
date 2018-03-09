#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int g_val = 100;
int main()
{
    pid_t id = vfork();
    int p_val = 1;

    if(id > 0)
    {
        //father
        printf("father id = %d,g_val = %d,address = %p\n",getpid(),g_val,&g_val);
        printf("father p_val = %d,address = %p\n",p_val,&p_val);

    }
    else if(id == 0)
    {
        //child
        g_val = 200;
        printf("child id = %d,g_val = %d,address = %p\n",getpid(),g_val,&g_val);
        p_val = 2;
        printf("father p_val = %d,address = %p\n",p_val,&p_val);
        //exit(1);
        return 1;
    }
    else
    {
        perror("vfork");
        exit(1);
    }

   // printf("process~\n");
    //exit(0);
    return 0;
}
