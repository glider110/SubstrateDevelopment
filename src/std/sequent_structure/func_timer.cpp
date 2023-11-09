/*
 * @Author: glider
 * @Date: 2023-10-15 11:10:08
 * @LastEditTime: 2023-11-09 19:13:41
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
#include <mutex>
#include <thread>
#include <unistd.h>

#include "key_monitor.h"
#include "manual_ctrl.h"

std::mutex number_mutex;

void otherFunction1(std::shared_ptr<int> para_ptr) {
    // 在这里编写你要调用的其他函数的代码
    std::cout << "调用定时触发函数xxxxxxxxxxxxxxxxxxxx......" << std::endl;
    // std::cout <<"参数1"<<a << std::endl;
    // std::lock_guard<std::mutex> lock(number_mutex);
    std::cout << "参数2:" << *para_ptr << std::endl;
}

void timerFunction(void (*funptr)(std::shared_ptr<int>),
                   std::shared_ptr<int> para_ptr, int interval) {
    std::cout << "loop numxxx: " << *para_ptr << std::endl;
    while (true) {
        std::cout << "loop num 1111 " << *para_ptr << std::endl;
        funptr(para_ptr);
        std::this_thread::sleep_for(
            std::chrono::milliseconds(interval)); // 等待指定的时间间隔
    }
}

class func_timer {
  private:
    /* data */
  public:
    func_timer(/* args */){};
    void timerFunction(int interval) {
        // key_monitor.init();      //FIXME(gxf):宏威这个终端格式不对且特别耗资源    
        key_control.enter_key_monitor();
        while (true) {
            // if (key_monitor.get_monitor('s'))
            if (key_control.get_monitor('s')) {
                std::cout << "loop num 1111 " << *para_ptr << std::endl;
                otherFunction1();
            }
            std::this_thread::sleep_for(
                std::chrono::milliseconds(interval)); // 等待指定的时间间隔
        }
    }

    void otherFunction1() {
        // 在这里编写你要调用的其他函数的代码
        std::cout << "调用定时触发函数xxxxxxxxxxxxxxxxxxxx......" << std::endl;
    }
    std::shared_ptr<int> para_ptr = std::make_shared<int>(100);

    // NS_KEY_MONITOR::KeyMonitor key_monitor;
    NS_MANUAL::ControlKey key_control;
};

int main() {
    bool isfrist = true;
    int count = 0;
    int para;
    int num = 0;
    std::shared_ptr<int> para_ptr = std::make_shared<int>(100);
    std::thread t;
    while (true) { //仿真回调功能
        num = count++;
        std::lock_guard<std::mutex> lock(number_mutex);
        *para_ptr = num;
        std::cout << "loop num: " << num << std::endl;
        // std::cout<<"loop num: " << *para_ptr<< std::endl;
        if (isfrist) {
            //  std::thread t=std::thread(timerFunction, otherFunction1,
            //  para_ptr, 2000); t.detach();
            func_timer timer;
            std::thread t = std::thread(&func_timer::timerFunction, &timer,
                                        100); // NOTE(gxf):特别注意下格式
                                              // 要用函数地址 取地址号类里用this
            t.detach();
            // static std::thread(timerFunction, otherFunction1,1000).detch();
            isfrist = false;
        }
        usleep(100 * 1000);
    }

    // 在这里编写其他函数的代码，这些函数将会在定时触发器运行的同时被执行

    return 0;
}