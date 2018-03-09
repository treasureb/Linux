#include<stdio.h>


int main()
{
    const char *msg1 = "Hello,printf!\n";
    const char *msg2 = "Hello,fwrite!\n";
    const char *msg3 = "Hello,write!\n";

    printf("%s",msg1);
    fwrite(msg2,strlen(msg2),1,stdout);
    write(1,msg3,strlen(msg3));
    fork();
    return 0;
}
