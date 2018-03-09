#include"common.h"
#include<stdio.h>
#include<unistd.h>

int main()
{
    int semid = CreateSem(1);
    if(semid < 0)
    {
        printf("CreateSem error!\n");
        return -1;
    }
    printf("semid=:%d\n",semid);
    SetSem(semid,0,1);
    pid_t id = fork();
    if(id > 0){
    //father
    while(1)
    {
      P(semid,0);
      printf("B");
      fflush(stdout);
      usleep(423 * 1000);
      printf("B");
      fflush(stdout);
      usleep(623 * 1000);
      printf(" ");
      V(semid,0);
    }
    }
      else if(id == 0){
        //child
      while(1)
     {
         int _semid = GetSem(0);
         P(_semid,0);
         printf("A");
         fflush(stdout);
         usleep(213 * 1000);
         printf("A");
         fflush(stdout);
         usleep(132 * 1000);
         printf(" ");
         V(_semid,0);
    }
      }
    else
    {
        perror("fork");
        return -3;
    }
    return 0;
}

