#include<stdio.h>
#include<string.h>

int main()
{
    FILE* fp = fopen("myfile","r");
    if(!fp)
    {
        printf("fopen error\n");
    }
#if 0
    const char *msg = "hello world\n";
    int count = 5;
    while(count--)
    {
       fwrite(msg,strlen(msg),1,fp);
    }
#endif
#if 1
    char buf[1024];
    const char *msg = "hello,bit!\n";

    while(1)
    {
        size_t s = fread(buf,1,strlen(msg),fp);
        if(s > 0)
        {
            buf[s] = 0;
            printf("%s",buf);
        }
        if(feof(fp))
            break;
    }
#endif
    fclose(fp);
    return 0;
}
