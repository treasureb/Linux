#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<sys/stat.h>


int main()
{
    if(chmod("hello.txt",0600) == -1){
        perror("chmod");
    }else{
        write(1,"Call chmod success.\n",20);
    }
}
