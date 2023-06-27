/*******************************************************************************
* Copyright (C) AnKobot Smart Tech Co., Ltd.  All Rights Reserved.
********************************************************************************
* File Name   : sleep_timer.h
* Author      : evan.zhang
* Version     : v0.01
* Date        : 2020-05-12
* Description : sleep定时器头文件定义
 * glider note:用在固定帧率的循环中,作为灵活sleep(),来至于光流打滑按时间段检测
*******************************************************************************/

#include "tool.h"

class SleepTimer
{
    public:

    SleepTimer(float frequency, uint64_t min_sleep_time = 1000);
    
    uint64_t sleep();

    private:

    uint64_t m_loop_ts_us;
    uint64_t m_min_sleep_time;
    uint64_t m_last_ts;
};