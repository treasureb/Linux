#include <stdio.h>
#include<signal.h>
#include<unistd.h>

void PrintSigset(sigset_t *set)
{
    int i = 1;
    for(;i < 32;++i)
    {
        if(sigismember(set,i))
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }
    }
    printf("\n");
}

int main()
{
    sigset_t newsig;
    sigset_t oldsig;
    sigemptyset(&newsig);
    sigaddset(&newsig,SIGINT);
    sigprocmask(SIG_BLOCK,&newsig,&oldsig);
    while(1)
    {
        sigpending(&newsig);
        PrintSigset(&newsig);
        sleep(1);
    }
    return 0;
}
