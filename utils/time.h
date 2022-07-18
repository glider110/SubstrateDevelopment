/*
 * @Author: wen.ligang
 * @Date: 2020-12-02 13:53:26
 * @LastEditTime: 2022-07-13 16:40:13
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @Description: 
 * @FilePath: /slam/src/common/time.h
 * @ 
 */
#ifndef SLAM_COMMON_TIME_H_
#define SLAM_COMMON_TIME_H_

#include <string>
#include <chrono>
#include <ostream>
#include <ratio>
// #include "common/port.h"

namespace slam {
namespace common {

constexpr int64_t kUtsEpochOffsetFromUnixEpochInSeconds =
    (719162ll * 24ll * 60ll * 60ll);

struct UniversalTimeScaleClock {
  using rep = int64_t;
  using period = std::ratio<1, 10000000>;
  using duration = std::chrono::duration<rep, period>;
  using time_point = std::chrono::time_point<UniversalTimeScaleClock>;
  static constexpr bool is_steady = true;
};

// Represents Universal Time Scale durations and timestamps which are 64-bit
// integers representing the 100 nanosecond ticks since the Epoch which is
// January 1, 1 at the start of day in UTC.
using Duration = UniversalTimeScaleClock::duration;
using Time = UniversalTimeScaleClock::time_point;

// Convenience functions to create common::Durations.
Duration FromSeconds(double seconds);
Duration FromMilliseconds(int64_t milliseconds);

// Returns the given duration in seconds.
double ToSeconds(Duration duration);
double ToSeconds(std::chrono::steady_clock::duration duration);

// Creates a time from a Universal Time Scale.
Time FromUniversal(int64_t ticks);

// Outputs the Universal Time Scale timestamp for a given Time.
int64_t ToUniversal(Time time);

// For logging and unit tests, outputs the timestamp integer.
std::ostream& operator<<(std::ostream& os, Time time);

// CPU time consumed by the thread so far, in seconds.
double GetThreadCpuTimeSeconds();

Time GetCurrentTime(void);
std::string GetCurrentDate(void);
} // namespace data_type
} // namespace slam

#endif