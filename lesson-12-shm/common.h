#ifndef __COMMON__
#define __COMMON__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>

#define PATHNAME "."
#define PROJ_TYPE 0x666

int CreateShm(int size);

int GetShm(int size);

int DestrorShm(int shmid);

#endif
