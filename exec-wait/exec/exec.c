#include<stdio.h>
#include<unistd.h>

int main()
{
    execl("/bin/ls","ls","-al",NULL);
    return 0;
}
