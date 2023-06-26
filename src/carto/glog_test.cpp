/*
 * @Author: glider
 * @Date: 2022-07-25 10:24:33
 * @LastEditTime: 2023-06-26 18:07:53
 * @FilePath: /SubstrateDevelopment/src/carto/glog_test.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */

#include <string>
#include <iostream>
#include <chrono>
#include "glog/logging.h"   // glog 头文件 
// #include "glog/raw_logging.h"
#include "timer.h"
using namespace std;

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



int main(int argc, char** argv){
    // FLAGS_log_dir = "/home/admins/桌面/github/SubstrateDevelopment/data/log";
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "/home/admins/project/SubstrateDevelopment/data/log/");
    // google::SetStderrLogging(google::GLOG_INFO);
    google::SetLogFilenameExtension("glider_log_");
    FLAGS_logtostderr = 0;  // glider note:将使日志信息记录到stderr(终端)而不保存到本地日志文件中，即使你设置了FLAGS_log_dir;()
    FLAGS_v = 1;
    FLAGS_minloglevel = -3;
    FLAGS_stderrthreshold = 0;
    // FLAGS_alsologtostderr = true;  //设置日志消息除了日志文件之外是否去标准输出
    FLAGS_colorlogtostderr = true;  //设置记录到标准输出的颜色消息（如果终端支持）
    FLAGS_log_prefix = true;  //设置日志前缀是否应该添加到每行输出
    FLAGS_logbufsecs = 0;  //设置可以缓冲日志的最大秒数，0指实时输出
    FLAGS_max_log_size = 10;  //设置最大日志文件大小（以MB为单位）
    FLAGS_stop_logging_if_full_disk = true;  //设置是否在磁盘已满时避免日志记录到磁盘

    VLOG(1) << "I'm printed when you run the program with --v=1 or higher";
    VLOG(2) << "I'm printed when you run the program with --v=2 or higher";
    std::string test = "this is test";
    int i = 2, number = 8;

    LOG(INFO) << "it is info";     // 打印log：“hello glog.  类似于C++ stream。
    LOG_IF(INFO, number > 10) << "number >  10"; 
    LOG_IF(INFO, number < 10) << "number <  10";
    for(i=0; i<20 ;i++){
        LOG_EVERY_N(INFO, 5) << "log i = " << i;
    }

    LOG(WARNING) << "It is error info"; 
    LOG(ERROR) << "It is error info"; 

    DLOG(INFO) << "it is debug mode";
    DLOG_IF(INFO, number > 10) << "debug number > 10";  
    // DLOG_EVERY_N(INFO, 10) << "log i = " << i;

    //有条件地中止程序
    int a1 = 5;
    // CHECK(a1 == 4) << "a1 != 4,fail!"; //a1 != 4的时候输出后面的打印，然后中止程序退出

    int a2 = 3;
    int a3 = 3;
    CHECK_EQ(a2,a3)<<"---==";//a2==a3的时候才继续运行  当a2！=a3的时候输出后面的打印退出中止运行



    LOG(WARNING) << "warning test";  //输出一个Warning日志
    LOG(ERROR) << "error test";  //输出一个Error日志
    //    LOG(FATAL) << "fatal test";  //输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序
    
    LOG(WARNING)<< NS_COMMON::GetCurrentTime();
    LOG(WARNING)<< NS_COMMON::ToUniversal(NS_COMMON::GetCurrentTime());
    sleep(0.1);
    LOG(WARNING)<< NS_COMMON::GetCurrentTime();
    LOG(WARNING)<< NS_COMMON::ToUniversal(NS_COMMON::GetCurrentTime());
    LOG(WARNING)<<NS_COMMON::GetCurrentDate();

    google::ShutdownGoogleLogging();
    std::cout<<"-------end-----"<<std::endl;
    return 0;
}
