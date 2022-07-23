/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-07-06 16:36:17
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-07-21 10:13:19
 * @FilePath: /SubstrateDevelopment/carto/glog_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <string>
#include <iostream>
#include "glog/logging.h"   // glog 头文件 
#include "glog/raw_logging.h"
#include  "../utils/time.h"

int main(int argc, char** argv){
    // FLAGS_log_dir = "/home/admins/桌面/github/SubstrateDevelopment/data/log";
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "/home/admins/桌面/github/SubstrateDevelopment/data/log/");
    // google::SetStderrLogging(google::GLOG_INFO);
    google::SetLogFilenameExtension("glider_log_");
    // FLAGS_logtostderr = true;  //设置日志消息是否转到标准输出而不是日志文件
    // FLAGS_alsologtostderr = true;  //设置日志消息除了日志文件之外是否去标准输出
    FLAGS_colorlogtostderr = true;  //设置记录到标准输出的颜色消息（如果终端支持）
    FLAGS_log_prefix = true;  //设置日志前缀是否应该添加到每行输出
    FLAGS_logbufsecs = 0;  //设置可以缓冲日志的最大秒数，0指实时输出
    FLAGS_max_log_size = 10;  //设置最大日志文件大小（以MB为单位）
    FLAGS_stop_logging_if_full_disk = true;  //设置是否在磁盘已满时避免日志记录到磁盘


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
    RAW_LOG(INFO, "it is pthread log");
    //    FLAGS_logtostderr = 1; // 将使日志信息记录到stderr而不保存到本地日志文件中，即使你设置了FLAGS_log_dir;
    FLAGS_alsologtostderr = true; //除了日志文件之外是否需要标准输出

    //有条件地中止程序
    int a1 = 5;
    // CHECK(a1 == 4) << "a1 != 4,fail!"; //a1 != 4的时候输出后面的打印，然后中止程序退出

    int a2 = 3;
    int a3 = 3;
    CHECK_EQ(a2,a3)<<"---==";//a2==a3的时候才继续运行  当a2！=a3的时候输出后面的打印退出中止运行



    LOG(WARNING) << "warning test";  //输出一个Warning日志
    LOG(ERROR) << "error test";  //输出一个Error日志
    //    LOG(FATAL) << "fatal test";  //输出一个Fatal日志，这是最严重的日志并且输出之后会中止程序


    
    
    LOG(WARNING)<< slam::common::GetCurrentTime();
    LOG(WARNING)<< slam::common::ToUniversal(slam::common::GetCurrentTime());
    sleep(0.1);
    LOG(WARNING)<< slam::common::GetCurrentTime();
    LOG(WARNING)<< slam::common::ToUniversal(slam::common::GetCurrentTime());
    LOG(WARNING)<<slam::common::GetCurrentDate();

    google::ShutdownGoogleLogging();


    std::cout<<"-------end-----"<<std::endl;
    return 0;
}
