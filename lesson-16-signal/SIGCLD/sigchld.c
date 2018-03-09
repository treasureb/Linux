#include <stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<stdlib.h>

#if 0
void Myhandler(sigset_t signal)
{
    printf("wait\n");
    wait(NULL);
}

int main()
{
    signal(SIGCHLD,Myhandler);
    pid_t id = fork();
    if(id > 0){
        //father
        while(1){
            printf("father doing some thing!\n");
            sleep(1);
        }
    }else if(id == 0){
        //child
        sleep(3);
        exit(1);
    }else{
        perror("fork");
        return 1;
    }
    return 0;
}
#endif

//void Myhandler(sigset_t signal)
//{
//    pid_t id;
//    while((id = waitpid(-1,NULL,WNOHANG) > 0))
//    {
//        printf("child wait success:%d\n",id);
//    }
//    printf("child is quit!\n");
//    printf("wait\n");
//    wait(NULL);

//}

int main()
{
    struct sigaction new,old;
    new.sa_handler = SIG_IGN;
    sigemptyset(&new.sa_mask);
    new.sa_flags = 0;
    sigaction(SIGCHLD,&new,&old);
    pid_t cid;
    int i = 0;
    for(;i < 20;++i)
    {
        cid = fork();
        if(cid == 0)
        exit(0);
    }
    if(cid > 0)
    {
        while(1)
        {
            printf("father doing some thing!\n");
            sleep(1);
        }
    }
    else if(cid == 0)
    {
        sleep(3);
    }
    sigaction(SIGCHLD,&old,NULL);
    return 0;
}
