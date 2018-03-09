#include"common.h"
#include<string.h>
#include<unistd.h>
int main()
{
    int msgid = GetMsg();
    printf("msgid = %d\n",msgid);

    char buf[1024] = {0};
    while(1)
     {
         printf("Input>\n");
         fflush(stdout);
         ssize_t read_size = read(0,buf,sizeof(buf) - 1);
         if(read_size < 0)
         {
             perror("read");
             return -1;
         }
         buf[read_size-1] = 0;
         int ret = SendMsg(msgid,CLIENT_TYPE,buf,sizeof(buf)-1);
         if(ret < 0)
         {
             printf("SendMsg faild\n");
             return -1;
         }
     }
    return 0;
}
