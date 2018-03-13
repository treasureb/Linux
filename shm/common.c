#include"common.h"

static int commonShm(int size,int flags)
{
    umask(0);
    key_t key = ftok(PATHNAME,PROJ_TYPE);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }
    
    int shmid = shmget(key,size,flags);
    if(shmid < 0)
    {
        perror("shmget");
        return -2;
    }

    return shmid;
}

int CreateShm(int size)
{
    return commonShm(size,IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm(int size)
{
    return commonShm(size,IPC_CREAT);
}

int DestroyShm(int shmid)
{
   int ret = shmctl(shmid,IPC_RMID,NULL);
   if(ret < 0)
   {
       perror("shmctl");
       return -3;
   }
   return 0;
}

