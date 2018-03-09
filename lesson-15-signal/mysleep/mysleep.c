#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void myhandler(sigset_t signal)
{
    //Do Nothing
    //if nodefine myhandler,then SIGALRM will exit pragma
}

unsigned int mysleep(unsigned int second)
{
    struct sigaction new,old;
    unsigned int unslept = 0;

    //empty the struct sigaction
    new.sa_handler = myhandler;
    sigemptyset(&new.sa_mask);
    new.sa_flags = 0;
    

    sigset_t new_mask,old_mask,suspmask;
    sigaction(SIGALRM,&new,&old);
    sigemptyset(&new_mask);
    sigaddset(&new_mask,SIGALRM);
    sigprocmask(SIG_BLOCK,&new_mask,&old_mask);
    

    alarm(second);
    suspmask = old_mask;
    sigdelset(&suspmask,SIGALRM);
    sigsuspend(&suspmask);
    unslept = alarm(0);

    sigaction(SIGALRM,&old,NULL);
    sigprocmask(SIG_SETMASK,&old_mask,NULL);
    return unslept;
}

int main()
{
    while(1)
    {
        mysleep(5);
        printf("5 second passed!\n");
    }
    return 0;
}
