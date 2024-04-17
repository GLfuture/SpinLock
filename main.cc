#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include "SpinLock.h"

#define THREADS_NUM     8
#define MAX_EXEC_TIMES  10000

galay::Util::SpinLock lock;

int global_num = 0;

void Func()
{
    for(int i = 0 ; i < MAX_EXEC_TIMES ; ++i)
    {
        lock.lock();
        ++global_num;
        lock.unlock();
    }
}


int main()
{
    auto start = std::chrono::system_clock::now();
    std::vector<std::thread> ths;
    for(int i = 0 ; i < THREADS_NUM ; ++i){
        ths.push_back(std::thread(Func));
    }
    for(int i = 0 ; i < THREADS_NUM ; ++i){
        if(ths[i].joinable()) ths[i].join();
    }
    auto end = std::chrono::system_clock::now();
    std::cout   << "res" << global_num <<\
    " cost : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";  
    return 0;
}