/*
 * @Author: wen.ligang
 * @Date: 2020-12-02 13:53:26
 * @LastEditTime: 2022-07-13 17:35:35
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @Description: 
 * @FilePath: /gros_ws/gros/slam/Slam/common/time.cc
 * @ 
 */


#include <time.h>

#include <cerrno>
#include <cstring>
#include <string>
#include <iostream>

#include "glog/logging.h"
#include "time.h"
namespace slam {
namespace common {

Duration FromSeconds(const double seconds) {
  return std::chrono::duration_cast<Duration>(
      std::chrono::duration<double>(seconds));
}

double ToSeconds(const Duration duration) {
  return std::chrono::duration_cast<std::chrono::duration<double>>(duration)
      .count();
}

double ToSeconds(const std::chrono::steady_clock::duration duration) {
  return std::chrono::duration_cast<std::chrono::duration<double>>(duration)
      .count();
}

Time FromUniversal(const int64_t ticks) { return Time(Duration(ticks)); }

int64_t ToUniversal(const Time time) { return time.time_since_epoch().count(); }

std::ostream& operator<<(std::ostream& os, const Time time) {
  os << std::to_string(ToUniversal(time));
  return os;
}

common::Duration FromMilliseconds(const int64_t milliseconds) {
  return std::chrono::duration_cast<Duration>(
      std::chrono::milliseconds(milliseconds));
}

double GetThreadCpuTimeSeconds() {
#ifndef WIN32
  struct timespec thread_cpu_time;
  CHECK(clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thread_cpu_time) == 0)
      << std::strerror(errno);
  return thread_cpu_time.tv_sec + 1e-9 * thread_cpu_time.tv_nsec;
#else
  return 0.;
#endif
}

// 系统启动到现在的时间
Time GetCurrentTime(void) {
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC/* CLOCK_REALTIME */, &current_time);
  uint64_t time_100ns = (current_time.tv_sec*1e9 + current_time.tv_nsec)/100;
  return Time(Duration(time_100ns));
}

// 当前日期
std::string GetCurrentDate(void) {
     // 基于当前系统的当前日期/时间
    time_t now = time(0); 
    // std::cout << "1970 到目前经过秒数:" << now << std::endl; 
    tm *ltm = localtime(&now); 
    // 输出 tm 结构的各个组成部分 
    // std::cout << "年: "<< 1900 + ltm->tm_year << std::endl; 
    // std::cout << "月: "<< 1 + ltm->tm_mon<< std::endl; 
    // std::cout << "日: "<< ltm->tm_mday << std::endl; 
    // std::cout << "时间: "<< ltm->tm_hour << ":"; 
    // std::cout << ltm->tm_min << ":"; 
    // std::cout << ltm->tm_sec << std::endl; 
    std::string date = std::to_string(1900 + ltm->tm_year) +  std::to_string(1 + ltm->tm_mon) +std::to_string(ltm->tm_mday)+    \
                                        std::to_string(ltm->tm_hour) +  std::to_string(ltm->tm_min) +std::to_string(ltm->tm_sec) ;                             
    return date;

}
}  // namespace common
}  // namespace slam

