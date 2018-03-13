#include"common.h"

int CommonSem(int nums,int flags)
{
    key_t key = ftok(PATHNAME,PROJ_TYPE);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }

    int semid = semget(key,nums,flags);
    if(semid < 0)
    {
        perror("semget");
        return -2;
    }

    return semid;
}

int CreateSem(int nums)
{
    return CommonSem(nums,IPC_CREAT | IPC_EXCL | 0666);
}

int GetSem(int nums)
{
    return CommonSem(nums,IPC_CREAT);
}

int SetSem(int semid,int nums,int value)
{
    union semun _semun;
    _semun.val = value;
    int ret = semctl(semid,nums,SETVAL,_semun);
    if(ret < 0)
    {
        perror("semctl setval");
        return -3;
    }
    return 0;
}

int CommonPV(int semid,int nums,int op)
{
    struct sembuf _sembuf;
    _sembuf.sem_num = nums;
    _sembuf.sem_op = op;
    _sembuf.sem_flg = 0;
    int ret = semop(semid,&_sembuf,1);
    if(ret < 0)
    {
        perror("semop");
        return -4;
    }
    return 0;
}

int P(int semid,int nums)
{
    return CommonPV(semid,nums,-1);
}

int V(int semid,int nums)
{
    return CommonPV(semid,nums,1);
}
