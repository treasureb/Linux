#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>

char *parse_cmd(char *cmd,char **argarr,int *narg){
    enum states{
        S_START,
        S_IN_TOKEN,
        S_IN_QUOTES,
        S_SEMI,
    };

    int argc = 0; //arg count
    int loop = 1; //Loop control

    enum states state = S_START;
    int lastch;

    while(loop){
        switch(state){
        case S_START:
            if(*cmd == '"'){
                *argarr++ = cmd+1;
                ++argc;
                state = S_IN_QUOTES;
            }else if(*cmd == 0 || *cmd == ';'){
                loop = 0;
            }else if(*cmd <= ' '){
                *cmd = 0;
            }else{
                *argarr++ = cmd;
                ++argc;
                state = S_IN_TOKEN;
            }
            break;

        case S_IN_TOKEN:
            if(*cmd == 0 || *cmd == ';'){
                loop = 0;
            }else if(*cmd <= ' '){
                *cmd = 0;
                state = S_START;
            }
        }
        cmd++;
    }
    *argarr = NULL;  //store the NULL pointer

    if(narg != NULL)
        *narg = argc;

    lastch = cmd[-1];
    cmd[-1] = 0;
    return lastch == ';'? cmd:NULL;
}

int main(int argc,char **argv){
    char cmd[80];   //input command area
    char *source = NULL;    //where commands to send to parser come from
    char *arg[21];  //arg list
    int statval;    //exec status value
    char *prompt = "maple:";    //command promt,with default
    char *test_env;    //getenv return value
    int numargs;    //parse_cmd return value

    if(test_env = getenv("PROMPT_ENVIRONMENT_VARIABLE"))
        prompt = test_env;
    while(1){
        if(source == NULL){
            printf("%s",prompt);
            source = gets(cmd);
            //source = cmd;
            if(source == NULL)
                exit(0);    //gets rtns NULL at EOF
        }

        //get the next command
        source = parse_cmd(source,arg,&numargs);
        if(numargs == 0)
            continue;

        //exit command
        if(!strcmp(arg[0],"exit")){
            if(numargs == 1)
                exit(0);
            if(numargs == 2){
                if(sscanf(arg[1],"%d",&statval) != 1){
                    fprintf(stderr,"%s:exit requires an integer status code\n",argv[0]);
                    continue;
                }
            exit(statval);
        }
        fprintf(stderr,"%s: exit takes one optional parameter -integer status\n",argv[0]);
        continue;
    }

    //run it
        if(fork() == 0){
            execvp(argv[0],arg);
            fprintf(stderr,"%s: EXEC of %s failed: %s\n",argv[0],arg[0],strerror(errno));
            exit(1);
        }
        wait(&statval);
        if (WIFEXITED(statval)){
            if(WEXITSTATUS(statval))
                fprintf(stderr,"%s:child exited with status %d\n",argv[0],WEXITSTATUS(statval));
        }else{
            fprintf(stderr,"%s:child died unexpectedly\n",argv[0]);
        }
    
    }
    return 0;
}
