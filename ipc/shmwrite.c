#include <stdio.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/types.h>

/*
 *
 * 在使用共享内存的时候，然后删除
 * 通过ipcs显示内存为0x00000000
 * 并且无法删除，因为在进程中已经进行删除了
 */
int main()
{
    int shmid;
    key_t key;
    char *shmaddr;
    if((key = ftok("/etc/profile",2)) == -1){
        perror("ftok");
    }
    if((shmid = shmget(key,4096,IPC_CREAT|0666)) == -1){
        perror("shmget");
    }
    shmaddr = shmat(shmid,NULL,0);
    sprintf(shmaddr,"hello this is a test");
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
    }
    return 0;
}
