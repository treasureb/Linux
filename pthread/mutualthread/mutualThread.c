#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>

pthread_mutex_t lock;
int g_count = 0;

void Modify()
{
    pthread_mutex_lock(&lock);
    printf("Before!\n");
    g_count++;
    sleep(3);
    printf("After!\n");
    pthread_mutex_unlock(&lock);
}

void* Myhandler(void* signal)
{
    (void)signal;
    Modify();
    return NULL;
}

void* ThreadEntry(void *arg)
{
    (void)arg;
    int i = 0;
    for(; i < 500000;i++)
    {
        Modify();
    }
    return NULL;
}

int main()
{
    signal(SIGINT,Myhandler);
    pthread_mutex_init(&lock,NULL);
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,ThreadEntry,NULL);
    pthread_create(&tid2,NULL,ThreadEntry,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&lock);
    printf("count:%d\n",g_count);
    return 0;
}
