#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#if 0
void* ThreadEntry(void *arg){
    (void) arg;
    while(1){
        printf("I am thread!\n");
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,ThreadEntry,NULL);
    printf("tid:%lx\n",tid);
    if(ret != 0){
        printf("pthread_create failed!%s\n",strerror(ret));
        return 1;
    }
    while(1){
        printf("main thread\n");
        printf("main thread ID:%lx\n",pthread_self());
        sleep(1);
    }
    return 0;
}
#endif

typedef struct Point{
    long x;
    long y;
}Point;

void* ThreadEntry(void *arg){
    (void) arg;
    printf("thread start!\n");
    sleep(3);
    printf("thread finish!\n");
    pthread_exit(NULL);
    
    Point* ret = (Point*)malloc(sizeof(Point));
    ret->x = 100;
    ret->y = 200;
    return (void*)ret;
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,ThreadEntry,NULL);
    printf("tid:%lx\n",tid);
    if(ret != 0){
        printf("pthread_create failed!%s\n",strerror(ret));
        return 1;
    }
    void* thread_ret = NULL;
    printf("before join\n");
    pthread_join(tid,(void*)&thread_ret);
    Point* pt = (Point*)thread_ret;
    printf("%ld,%ld\n",pt->x,pt->y);
    printf("after join\n");
    while(1){
        printf("main thread\n");
        printf("main thread ID:%lx\n",pthread_self());
        sleep(1);
    }
    return 0;
}

