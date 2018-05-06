#include <stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void Sigroutine(int signo)
{
    switch(signo){
    case 2:
        printf("Get a signal SIGINT\n");
        break;
    case 3:
        printf("Get a signal SIGQUIT\n");
        break;
    case 15:
        printf("Get a signal SIGTERM\n");
        break;
    }
}

int main()
{
    printf("precess id is %d.\n",getpid());
    signal(SIGTERM,Sigroutine);
    signal(SIGINT,Sigroutine);
    signal(SIGQUIT,Sigroutine);
    while(1);

    return 0;
}

