#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>

#if 0
void Myhandler(int sig)
{
    printf("sig=%d\n",sig);
}

void* ThreadEntry(void *arg)
{
    (void) arg;
    while(1)
    {
        printf("Thread 1\n");
        sleep(1);

        int *ptr = NULL;
        *ptr = 100;//执行到这一行触发
    }
    return NULL;
}
int main()
{
    signal(SIGSEGV,Myhandler);
    pthread_t tid;
    pthread_create(&tid,NULL,ThreadEntry,NULL);
    pthread_detach(tid);//分离之后，线程退出后自动释放其内存
    while(1)
    {
        printf("main thread\n");
        sleep(3);
    }
    return 0;
}
#endif


#if 0
void* ThreadEntry(void *arg)
{
    (void) arg;
    while(1)
    {
        ;
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,ThreadEntry,NULL);
    pthread_detach(tid);//分离之后，线程退出后自动释放其内存
    while(1)
    {
        ;
    }
    return 0;
}
#endif


__int64_t TimeStamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
}

void Calc(int *array,size_t beg,size_t end)
{
    size_t i = beg;
    for(;i < end;++i)
    {
        int tmp = array[i];
        array[i] = tmp * tmp;
    }
}

#if 0
int main()
{
    const size_t size = 100000000;
    int *array = (int *) malloc(size * sizeof(array));
    __int64_t beg = TimeStamp(); 
    Cala(array,0,size);
    //多台服务器时，可能减出来一个负数
    __int64_t end = TimeStamp();
    printf("time:%ld\n",end - beg);
    return 0;
}
#endif

//给每个线程的入口函数传一个结构体
typedef struct Context
{
    int *array;
    size_t beg;
    size_t end;
}Context;


void* ThreadEntry(void *arg)
{
    Context* context = (Context*)arg;
    Calc(context->array,context->beg,context->end);
    return NULL;
}

int main()
{
    const size_t size = 100000000;
    int *array = (int*)malloc(size * sizeof(int));
   
    int thread_size = 0;
    while(1)
    {
         printf("Input>\n");
         scanf("%d",&thread_size);
         pthread_t tid[thread_size];
         int i = 0;
         Context context[thread_size];
         __int64_t beg = TimeStamp();
         size_t index_base = 0;
         for(;i < thread_size;++i)
         {
             context[i].array = array;
             context[i].beg = index_base;
             context[i].end = index_base + size / thread_size;
             index_base += size / thread_size;
             pthread_create(&tid[i],NULL,ThreadEntry,&context[i]);
         }
         for(i = 0;i < thread_size;++i)
         {
             pthread_join(tid[i],NULL);
         }
         __int64_t end = TimeStamp();
         printf("Operator time:%ld\n",end - beg);
         printf("---------------------------------\n");
    }
    return 0;
}
