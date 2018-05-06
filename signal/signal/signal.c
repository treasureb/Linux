#include <stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void HandleSigint(int signo)
{
    printf("receive signal %d.\n",signo);
}
int main()
{
    if(signal(SIGINT,HandleSigint) == SIG_ERR){
        perror("signal");
        exit(0);
    }
    pause();
}
