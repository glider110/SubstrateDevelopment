/*
 * @Author: wen.ligang
 * @Date: 2020-12-02 13:53:26
 * @LastEditTime: 2020-12-02 18:20:52
 * @LastEditors: wen.ligang
 * @Description: 
 * @FilePath: /slam/src/common/port.h
 * @ 
 */
#ifndef SLAM_COMMON_PORT_H
#define SLAM_COMMON_PORT_H

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <cinttypes>
#include <cmath>
#include <string>

namespace slam {
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
namespace common {

} // namespace common
} // namespace slam

#endif
