#ifndef __COMMON__
#define __COMMON__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>


#define PATHNAME "."
#define PROJ_TYPE 0x666

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
    void *__pad;
};

int CreateSem(int nums);

int GetSem(int nums);

int SetSem(int semid,int nums,int value);

int P(int semid,int nums);

int V(int semid,int nums);
#endif
