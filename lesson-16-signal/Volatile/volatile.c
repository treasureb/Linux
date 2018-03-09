#include<stdio.h>
#include<signal.h>

volatile int g_val = 0;

void my_handler(int signal)
{
    g_val = 1;
    printf("%d\n",g_val);
}

int main()
{
    signal(SIGINT,my_handler);
    while(g_val == 0)
    {
        ;
    }
    printf("%d\n",g_val);
    return 0;
}
