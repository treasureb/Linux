/*
 *保存结果的地方位于静态内存中
 *上次的结果会被下次的结果覆盖掉
 *多线程环境会出现线程不安全的情况
 */ 


/*
 * inet_ntop函数自己传入一段空间
 * 从而避免了inet_ntoa函数
 */

#include<netinet/in.h>
#include<stdint.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>

int main()
{
    struct sockaddr_in addr1;
    struct sockaddr_in addr2;
    uint32_t ip1 = 0;
    uint32_t ip2 = 0xffffffff;
    addr1.sin_addr.s_addr = ip1;
    addr2.sin_addr.s_addr = ip2;
    char* str1 = inet_ntoa(addr1.sin_addr);
    char* str2 = inet_ntoa(addr2.sin_addr);
    printf("str1=%s\n",str1);
    printf("str2=%s\n",str2);
}
