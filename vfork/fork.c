#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>

int main()
{
    int i = 0;
    for(; i < 2;i++)
    {
        fork();
        printf("-");
        fflush(stdout);
    }
    //printf("\n");
    wait(NULL);
    wait(NULL);
    return 0;
}
