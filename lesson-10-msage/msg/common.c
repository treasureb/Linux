#include"common.h"
#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<errno.h>
#include<string.h>
#include<sys/msg.h>
#include<stdlib.h>


int CommonMsg(int flags)
{
    key_t id = ftok(PATHNAME,PROJ_ID);
    if(id == -1)
    {
        perror("ftok");
        return -1;
    }
    int msgid = msgget(id,flags);
    if(msgid < 0)
    {
        perror("msgget");
/*        exit(-1);*/
        return -1;
    }
    return msgid;
}

int CreateMsg()
{
    return CommonMsg(IPC_CREAT |IPC_EXCL | 0666);
}

int GetMsg()
{
    return CommonMsg(IPC_CREAT);
}

int DestroyMsg(int msg_id)
{
   int ret =  msgctl(msg_id,IPC_RMID,NULL);
   if(ret < 0)
   {
       perror("msgctl");
       return -1;
   }

   return 0;
}

int SendMsg(int msg_id,long type ,char* buf,size_t size)
{
    MsgBuf msgbuf;
    msgbuf.type = type;
    if(size > sizeof(msgbuf.text) - 1)
    {
        printf("Size too larger");
        return -1;
    }
    strcpy(msgbuf.text,buf);
    int ret =  msgsnd(msg_id,&msgbuf,sizeof(buf),0);
    if(ret < 0)
    {
        perror("msgsnd");
        return -1; 
    }
    return 0;
}

int RecvMsg(int msg_id,long type,char* buf,size_t size)
{
    MsgBuf msgbuf;
    ssize_t ret =  msgrcv(msg_id,&msgbuf,sizeof(msgbuf.text),type,0);
    if(ret < 0 )
    {
        perror("msgrcv");
        return -1;
    }
    strcpy(buf,msgbuf.text);
    return 0;

}
