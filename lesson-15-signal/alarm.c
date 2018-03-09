#include <stdio.h>
#include<unistd.h>
#include<signal.h>

size_t g_count = 0;

void myhander(int sig)
{
    printf("%lu\n",g_count);
    return;
}
int main()
{
    alarm(1);
    while(1)
    {
        signal(SIGALRM,myhander);
        ++g_count;
 //       printf("%lu,",g_count);
    }
    return 0;
}
