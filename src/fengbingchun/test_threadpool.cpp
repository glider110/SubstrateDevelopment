/*
 * @Author: glider
 * @Date: 2023-06-28 14:01:16
 * @LastEditTime: 2023-06-28 14:58:51
 * @FilePath: /SubstrateDevelopment/src/fengbingchun/test_threadpool.cpp
 * @Version:  v0.01
 * @Description: 极简的线程池实现,用起来甚至比线程还方便
 * glider url:https://github.com/progschj/ThreadPool
 * glider url:https://github.com/glider110/3D_map/blob/main/process/process.cpp
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include "funset.hpp"
#include "ThreadPool.h"
#include "iostream"
#include <vector>
#include <chrono>

#define LOG(x)   std::cout << x <<std::endl
void test_thredpool()
{
    auto lamda=[](int a){
        LOG("快速开辟线程...");
        LOG(a);
    };
    //method:线程
    std::thread thread_test(lamda,10);
    thread_test.detach();
    std::make_shared<std::thread>(std::bind(lamda, 11))->detach();
    std::make_shared<std::thread>(std::bind(lamda, placeholders::_1),12)->detach();
    usleep(10);

    //method:线程池(一)
    ThreadPool threadpool(6);
    threadpool.enqueue(lamda,10);

    //method:线程池(二)
    // create thread pool with 4 worker threads
    ThreadPool pool(4);
    // enqueue and store future
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    // get result from future
    std::cout << result.get() << std::endl;


    // //method:线程池(三)
    ////glider !:这个没有等待一起完成在执行后续操作,看业务需求,如果是避障项目需要等待所有检测结束再融合
    // ThreadPool pool(4);
    // std::vector< std::future<int> > results;
    // for(int i = 0; i < 8; ++i) {
    //     results.emplace_back(
    //         pool.enqueue([i] {
    //             std::cout << "hello " << i << std::endl;
    //             std::this_thread::sleep_for(std::chrono::seconds(1));
    //             std::cout << "world " << i << std::endl;
    //             return i*i;
    //         })
    //     );
    // }

    // for(auto && result: results)
    //     std::cout << result.get() << ' ';
    // std::cout << std::endl;

}



    