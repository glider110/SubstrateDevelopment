/*
 * @Author: glider
 * @Date: 2022-08-03 14:12:02
 * @LastEditTime: 2022-08-03 14:16:48
 * @FilePath: /SubstrateDevelopment/design_patterns/Singleton_qiu.h
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */
/**
 * @file lidar_loop.h
 * @author qiulinliu (qiulin.liu@ankobot.com)
 * @brief:
 * @version 0.1
 * @date 2022-06-17
 *
 * Copyright (c) 2022 AnKobot Co., Ltd. All rights reserved.
 *
 */
#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "node_comm/msg_defines.h"
#include "node_comm/publication.hpp"
#include "ydlidar_s2pro/include/CYdLidar.h"

namespace sensor {

class LidarLoop {
public:
    LidarLoop(const LidarLoop&)            = delete;
    LidarLoop(LidarLoop&&)                 = delete;
    LidarLoop& operator=(const LidarLoop&) = delete;
    LidarLoop& operator=(LidarLoop&&)      = delete;

    static std::shared_ptr<LidarLoop> GetInstance();

    void Run(int argc, char* argv[]);

    void ShutdownLidar();

protected:
    LidarLoop();

private:
    static std::shared_ptr<LidarLoop> instance_;
    static std::mutex                 instance_mutex_;

    const std::string                     k_lidar_port_;
    const uint32_t                        k_lidar_baudrate_;
    const float                           k_lidar_frequency_;
    const int                             k_lidar_abnormal_check_count_;
    const bool                            k_lidar_fixed_resolution_;
    const bool                            k_lidar_reversion_;
    const bool                            k_lidar_inverted_;
    const bool                            k_lidar_auto_reconnect_;
    const bool                            k_lidar_intensity_;
    const float                           k_lidar_max_angle_;
    const float                           k_lidar_min_angle_;
    const float                           k_lidar_max_range_;
    const float                           k_lidar_min_range_;
    CYdLidar                              lidar_;
    nodecomm::PublicationData<LidarFrame> pub_lidar_{HID_SENSOR, FID_LIDAR_DATA};

    void ThreadRecvData(int argc, char* argv[]);
};

}  // namespace sensor
