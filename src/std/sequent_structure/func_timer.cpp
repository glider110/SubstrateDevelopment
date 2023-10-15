/*
 * @Author: glider
 * @Date: 2023-10-15 11:10:08
 * @LastEditTime: 2023-10-15 11:46:07
 * @FilePath: /SubstrateDevelopment/src/std/sequent_structure/func_timer.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

void otherFunction1()
{
    // 在这里编写你要调用的其他函数的代码
    std::cout << "调用定时触发函数xxxxxxxxxxxxxxxxxxxx......" << std::endl;
}

void otherFunction2()
{
    // 在这里编写你要调用的其他函数的代码
    std::cout << "调用定时触发函数oooooooooooooooo......" << std::endl;
}

void timerFunction(void (*func)(), int interval)
{
    // while (true)
    {
        func(); // 调用传入的函数指针
        std::this_thread::sleep_for(std::chrono::milliseconds(interval)); // 等待指定的时间间隔
    }
}

int main()
{
int count =0;
    while (true)
    {
        std::cout << count++ << std::endl;
        
        std::thread t1(timerFunction, otherFunction1, 1000); // 创建一个线程，调用timerFunction函数，传入otherFunction函数指针和触发间隔1秒钟（1000毫秒）
        // std::thread t2(timerFunction, otherFunction2, 500); // 创建一个线程，调用timerFunction函数，传入otherFunction函数指针和触发间隔1秒钟（1000毫秒）
        t1.detach(); // 等待线程结束
        // t2.detach(); // 等待线程结束
        //     t1.join(); // 等待线程结束
        //  t2.join(); // 等待线程结束
        usleep(100*1000);
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