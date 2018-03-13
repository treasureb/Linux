#include"common.h"

int main()
{
    int shm_id = CreateShm(4096);
    if(shm_id < 0)
    {
        printf("CreateShm error!\n");
        return -1;
    }

    char *ptr =shmat(shm_id,NULL,0);
    while(1)
    {
        printf("Client say>%s\n",ptr);
        fflush(stdout);
        sleep(1);
    }
    shmdt(ptr);
    return 0;
}
