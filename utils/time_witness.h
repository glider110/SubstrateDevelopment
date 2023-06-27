/*
 * @Author: glider
 * @Date: 2023-06-27 19:33:03
 * @LastEditTime: 2023-06-28 00:45:52
 * @FilePath: /SubstrateDevelopment/utils/time_witness.h
 * @Version:  v0.01
 * @Description: 
 * glider note:计时器 来至于重定位业务逻辑需要记时判断重定位成功与否
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#ifndef TIME_WITNESS_H_
#define TIME_WITNESS_H_

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <ctime>

using Time = std::chrono::time_point<std::chrono::system_clock>;

namespace NS_COMMON {
class TimeWitness {
  public:
    TimeWitness(std::string name):name_(name) {};
    Time StartRecord(void);
    Time StopRecord(void);
    Time StopRecord(double &time_ms);
    bool IsRecording(void) {
      return IsStarting_;
    }
    double msTimePasses(void);
  private:
    std::string name_;
    Time start_time_,stop_time_;
    bool IsStarting_ = false;
};

} // namespace NS_COMMON


#endif