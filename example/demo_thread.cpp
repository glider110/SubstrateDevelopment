#include <iostream>
#include <map>
#include <memory>
#include <string.h>
#include <vector>
#include <map>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <mutex>
#include <chrono>
#include <iomanip>
/*多线程:主要有三个内容(看看源码结构)
**1.线程构造
**2.线程柱塞和分离
**3.多线程同步:解决写入同一块内存数据存在错误问题;   
*/

/*开发中可能遇到的场景:
**1.无数据写入 障碍物识别案例
**2.有数据读写 下面这个加锁案例
**3.一线程抛 一线程收   光流案例
*/

using namespace std;
#define MAX 100


int number = 0;
int number_1 = 0;
mutex number_mutex;

inline static uint64_t getSystemTimestampUS()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec * 1e6 + ts.tv_nsec * 0.001);
}

void test_chrono()
{
    // 获取当前系统时间点
    //方法(一)
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    std::time_t c = std::chrono::system_clock::to_time_t(t);
    sleep(1);
    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    std::time_t c1 = std::chrono::system_clock::to_time_t(t1);
    cout << std::put_time(std::localtime(&c), "%F %T\n");    //  2022-02-22 20:50:30
    cout << std::put_time(std::localtime(&c1), "%F %T\n");    //  2022-02-22 20:50:30
    //方法(二)
    uint64_t timestamp1 = getSystemTimestampUS() / 1000;
    sleep(1);
    uint64_t timestamp2 = getSystemTimestampUS() / 1000;
    cout << timestamp1 <<endl;
    cout << timestamp2<<endl;
    //获取程序的耗时（相当于秒表）
    auto t11 = std::chrono::steady_clock::now();
    sleep(1);
    auto t22 = std::chrono::steady_clock::now();
    cout << "<======= opticalflow3 time "<< std::chrono::duration_cast<std::chrono::microseconds>(t22 - t11).count()/1000<< " ms" << endl;
}


void thread1()
{
    // int i = 0;
    // while (1)
    // {
    //     cout << "thread1111:" << i++ << endl;
    //     // sleep(1);  //不能是小数
    //     usleep(1);
    // }
    for (size_t ii= 0; ii < MAX/2; ii++)
    {       
        // number_mutex.lock();
        lock_guard<mutex>  lock(number_mutex);
        int cur = number;
        cur++;
        usleep(1000);
        number = cur;
        cout << "thread1111:" << number << endl;
        // number_mutex.unlock();
        // usleep(10);
        // cout << "thread1111:" << number_1++ << endl;

    }
    
}


void thread2()
{
    // int i = 0;
    // while(1)
    // {
    //     cout << "thread2222:" << i++ << endl;
    //     usleep(1);
    // }
    for (size_t ii= 0; ii < MAX/2; ii++)
    {
        // number_mutex.lock();
        lock_guard<mutex>  lock(number_mutex);
        int cur = number;
        cur++;
        usleep(10);            //一旦阻塞就去资源就去别的线程了  而这个线程写入共享数据还没结束就用在其他地方用了 那必须上锁保持同步
        number = cur;
        cout << "thread2222:" <<  number << endl;
        // number_mutex.unlock();

        // usleep(10);
        // cout << "thread2222:" << number_1++ << endl;
    }
}

int main(int argc, char **argv) {
    thread test1_handle, test2_handle;
    // thread1();
    do
    {
    test1_handle = std::thread(thread1);  //可以通过lamda 仿函数构造
    test2_handle = std::thread(thread2);
    // test1_handle.join();
    test1_handle.detach();
    test2_handle.detach();
    cout << "主线程:\n"  << endl;
    }
    while(0);
    // test_chrono();
    // thread t1(func1);
    // std::thread(thread2);
    // sleep(10);    //主线程结束　子线程也结束　一般情况下主线程会阻塞在那里或者sleep一下；
    while (1) {sleep(1);}


    return 0;
}

