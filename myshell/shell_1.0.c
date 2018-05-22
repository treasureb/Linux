#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<errno.h>

#define SHELL_NAME "sh1"
#define PROMPT_ENVIRONMENT_VARIABLE "PROMPT"

char* prompt;

int main(int argc,char* argv[]){
    char cmd[80];
    int statval;

    if((prompt = getenv(PROMPT_ENVIRONMENT_VARIABLE)) == NULL)
        prompt = SHELL_NAME ":";

    while(1){
        printf("%s",prompt);
        gets(cmd);

        if(strcasecmp(cmd,"exit") == 0)
            break;

        if(fork() == 0){
            execlp(cmd,cmd,NULL);
            fprintf(stderr,"%s: Exec %s failed: %s\n",argv[0],cmd,strerror(errno));
            exit(1);
        }

        wait(&statval);
        if(WIFEXITED(statval)){
            if(WEXITSTATUS(statval)){
                fprintf(stderr,"%s:child exited with status %d.\n",argv[0],WEXITSTATUS(statval));
            }
        }else{
            fprintf(stderr,"%s:child died unexpectedly.\n",argv[0]);
        }
    }

    return 0;
}
