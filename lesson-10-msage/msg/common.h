#ifndef __COMMON__
#define __COMMON__

#include<stdio.h>
#define PATHNAME "."
#define PROJ_ID 0x666
#define CLIENT_TYPE 1
#define SERVER_TYPE 2
#define MaxSize 1024

typedef struct MsgBuf
{
    long type;
    char text[MaxSize];
}MsgBuf;

int CreateMsg();

int GetMSg();

int DestroyMsg(int msg_id);

int SendMsg(int msg_id,long type,char* buf,size_t size);

int RecvMsg(int msg_id,long type,char* buf,size_t size);
#endif
