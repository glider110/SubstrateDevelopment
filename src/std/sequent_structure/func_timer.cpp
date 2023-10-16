/*
 * @Author: glider
 * @Date: 2023-10-15 11:10:08
 * @LastEditTime: 2023-10-16 12:15:13
 * @FilePath: /SubstrateDevelopment/src/std/sequent_structure/func_timer.cpp
 * @Version:  v0.01
 * @Description:实现定时器功能,每隔一个时间段触发自定义函数
 * 应用:可以用来触发保存数据,也可以用来触发参数更新;
 * ps:传入的参数用指针可以,用引用不行;
 *        线程并发问题;
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved.
 * ************************************************************************
 */
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>


std::mutex number_mutex;


void otherFunction1( std::shared_ptr<int> para_ptr) {
        // 在这里编写你要调用的其他函数的代码
        std::cout << "调用定时触发函数xxxxxxxxxxxxxxxxxxxx......" << std::endl;
        // std::cout <<"参数1"<<a << std::endl;
        // std::lock_guard<std::mutex> lock(number_mutex);
        std::cout <<"参数2:"   <<*para_ptr << std::endl;
}

void otherFunction2() {
    // 在这里编写你要调用的其他函数的代码
    std::cout << "调用定时触发函数oooooooooooooooo......" << std::endl;
}

void timerFunction( void(*funptr)(std::shared_ptr<int>) , std::shared_ptr<int> para_ptr, int interval) {
    std::cout<<"loop numxxx: " << *para_ptr<< std::endl;
    while (true)
    {
        std::cout<<"loop num 1111 " << *para_ptr<< std::endl;
        funptr(para_ptr);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval)); // 等待指定的时间间隔
    }
}

int main() {
    bool isfrist = true;
    int count = 0;
    int para;
    int num =0;
    std::shared_ptr<int> para_ptr = std::make_shared<int>(100);
    // static std::thread t;
     std::thread t;
    while (true) {//仿真回调功能
        num = count++;
        std::lock_guard<std::mutex> lock(number_mutex);
        *para_ptr =num;
        std::cout<<"loop num: " << num<< std::endl;
        std::cout<<"loop num: " << *para_ptr<< std::endl;
        if (isfrist) {
             std::thread t=std::thread(timerFunction, otherFunction1, para_ptr, 2000);
             t.detach();
            // static std::thread(timerFunction, otherFunction1,1000).detch();
            isfrist = false;
        }
        // std::thread t2(timerFunction, otherFunction2, 500); //
        // 创建一个线程，调用timerFunction函数，传入otherFunction函数指针和触发间隔1秒钟（1000毫秒）
        // t2.detach(); // 等待线程结束
        //     t1.join(); // 等待线程结束
        //  t2.join(); // 等待线程结束
        usleep(100 * 1000);
        std::cout << "调用了其他函数" << std::endl;
    }

    // 在这里编写其他函数的代码，这些函数将会在定时触发器运行的同时被执行

    // t1.join(); // 等待线程结束
    // t2.join(); // 等待线程结束
    //     while (true)
    //    {
    //     usleep(100*1000);
    //     std::cout << "调用了其他函数" << std::endl;
    //    }

    return 0;
}