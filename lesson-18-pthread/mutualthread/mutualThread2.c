#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t g_cond;
pthread_mutex_t g_mutex;

void* ThreadEntry1(void* arg)
{
    (void)arg;
    while(1)
    {
        printf("传球\n");
        pthread_cond_signal(&g_cond);
        usleep(678123);
    }
    return NULL;
}

void* ThreadEntry2(void* arg)
{
    (void)arg;
    while(1)
    {
        pthread_cond_wait(&g_cond,&g_mutex);
        printf("投篮\n");
        usleep(123456);
    }
}
int main()
{
    pthread_t tid1,tid2;
    pthread_cond_init(&g_cond,NULL);
    pthread_mutex_init(&g_mutex,NULL);
    pthread_create(&tid1,NULL,ThreadEntry1,NULL);
    pthread_create(&tid2,NULL,ThreadEntry2,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
}
