#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    key_t key1,key2,key3;
    if((key1 = ftok("/etc/profile",1)) == -1){
        perror("ftok");
        exit(1);
    }
    if((key2 = ftok("/etc/profile",2)) == -1){
        perror("ftok");
        exit(2);
    }
    if((key3 = ftok("/etc/profile",3)) == -1){
        perror("ftok");
        exit(3);
    }
    printf("key1 = %d\n key2 = %d\n key3 = %d\n",key1,key2,key3);
    return 0;
}
