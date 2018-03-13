#include"common.h"

int main()
{
    int msgid = CreateMsg();
    printf("msgid = %d\n",msgid);
    char buf[1024] = {0};
    while(1)
    {
        RecvMsg(msgid,CLIENT_TYPE,buf,sizeof(buf));
        printf("client say>%s\n",buf);
        
        SendMsg(msgid,SERVER_TYPE,buf,sizeof(buf));
        printf("send done,wait recv!\n");
    }
    

    return 0;
}
