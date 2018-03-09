#include"common.h"
#include<sys/types.h>
#include<sys/shm.h>
#include<unistd.h>

int main()
{
    int shmid = GetShm(1024);
    if(shmid < 0)
    {
        printf("CreateShm error!\n");
        return -1;
    }
    char *ptr = shmat(shmid,NULL,0);
    int i = 0;
    while(1)
    {
        ptr[i] = 'A' + i;
        i++;
        ptr[i] = 0;
        sleep(1);
        i %= 26;
    }
    shmdt(ptr);
    return 0;
}
