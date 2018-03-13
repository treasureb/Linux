#include <stdio.h>
#include<stdlib.h>
#include<signal.h>

int main(int argc,char *argv[])
{
    if(argc < 3)
    {
        printf("Usage:kill  [signo] [pid]\n");
        return 1;
    }
    int pid = atoi(argv[2]);
    int sig = atoi(argv[1]);
    int ret = kill(pid,sig);
    if(ret < 0)
    {
        perror("kill");
        return -1;
    }

    return 0;
}
