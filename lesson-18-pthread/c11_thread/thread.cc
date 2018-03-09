#include <cstdio>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<condition_variable>

std::atomic_int g_count = 0;

class T{
public:
    T(const T& ) = delete;//禁止拷贝
    T& operator=(const T& ) = delete;
};

void ThreadEntry(){
//    while(1){
       // lock->lock();
       // std::lock_guard<std::mutex> guard(*lock);//起到智能指针的作用
        /*这样的逻辑要在每一次函数调用中都要解锁，否则就会产生死锁
         * 可以使用RAII
         *
  
        if(cond1){
            continue;
        }

        if(cond2){
            break;
        }

        if(cond3){
            return;
        }
        */
        int i = 0;
        for(;i < 50000;i++){
            g_count++;
        }
      //  printf("In thread:%d \n",g_count);
       // lock->unlock();
       // sleep(1);
//    }
}

int main(){
    int a = 10;
    int b = 20;
    std::mutex lock;//创建即初始化，初始状态是未加锁，并且不能拷贝
    std::thread t1(ThreadEntry);
    std::thread t2(ThreadEntry);
    t1.join();
    t2.join();
    printf("In thread:%d \n",g_count);
    //t1.detach();
    return 0;
}
