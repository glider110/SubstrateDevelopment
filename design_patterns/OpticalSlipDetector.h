/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-07-28 16:08:23
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-07-28 16:22:33
 * @FilePath: /SubstrateDevelopment/design_patterns/OpticalSlipDetector.h
 * @Description: 
 * 
 * Copyright (c) 2022 by 郭小凡 glider.guo@ankobot.com, All Rights Reserved. 
 */
/*******************************************************************************
* Copyright (C) AnKobot Smart Tech Co., Ltd.  All Rights Reserved.
********************************************************************************
* File Name   : OpticalSlipDetector.h
* Author      : evan.zhang
* Version     : v0.01
* Date        : 2022-03-01
* Description : 光流打滑检测接口
*******************************************************************************/

#ifndef _OPTICAL_SLIP_DETECTOR_H_
#define _OPTICAL_SLIP_DETECTOR_H_

#include "ak_message_bus.h"
#include "ak_message_cmd_cam.h"
#include "ThreadPool.h"

#include <memory>
#include <queue>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <thread>


#include "plan_data.h"
#include "slip_data.h"
#include "SkidDetection.h"

class OpticalSlipDetector;
using OpticalSlipDetectorPtr = std::shared_ptr<OpticalSlipDetector>;

class OpticalSlipDetector
{
public:

    /**
      * @brief  获取OpticalSlipDetector对象的单例
      * @param  None
      * @retval 单例对象shared_ptr对象
      */
    static OpticalSlipDetectorPtr getInstance(
        AKShareQueue<FrameBufQueue> *cam_data_queue_ptr,
        ThreadPool *pool_ptr);

    // 禁止拷贝构造和赋值函数
    OpticalSlipDetector(const OpticalSlipDetector &) = delete;
    void operator=(const OpticalSlipDetector &) = delete;

    ~OpticalSlipDetector();

    /**
      * @brief  开始检测
      * @param  None
      * @retval bool    全局规划器是否成功开始执行，true成功，false失败
      */
    bool startDetect();

    /**
      * @brief  停止检测
      * @param  None
      * @retval None
      */
    void stopDetect();

    /**
      * @brief  向检测器喂位姿数据
      * @param  pose_data   最新的位姿数据
      * @retval None
      */
    void feedPoseData(const PlanData &pose_data);

    /**
      * @brief  获取检测结果
      * @param  None
      * @retval None
      */
    SlipData getFlag() const;

private:
    /**
         * @brief  构造函数
         * @param  cam_data_queue_ptr   图像帧数据队列指针，存放图像帧数据
         * @param  pool_ptr             线程池对象指针
         * @retval None
         */
    OpticalSlipDetector(AKShareQueue<FrameBufQueue> *cam_data_queue_ptr,
                        ThreadPool *pool_ptr);

    /**
      * @brief  检测线程函数
      * @param  None
      * @retval None
      */
    void detecting();

    /**
      * @brief  重置检测相关数据
      * @param  None
      * @retval None
      */
    void clearDetectFlag();

    using SlipInputData = std::pair<FrameBufQueue *, PlanData *>;

    bool m_run;
    bool m_need_stop;

    std::queue<PlanData> m_pose_queue;
    std::list<PlanData> m_pose_data;
    AKShareQueue<FrameBufQueue> *m_cam_data_queue_ptr;
    ThreadPool *m_pool_ptr;

    PlanData m_pose_buf1, m_pose_buf2;
    FrameBufQueue m_cam_buf1, m_cam_buf2;

    PlanData *m_new_pose_ptr;
    FrameBufQueue *m_new_cam_ptr; 

    SlipInputData m_last_input, m_cur_input;

    SlipData m_slip_flag;
    
    std::mutex m_feed_mtx;
    std::mutex m_detect_mtx;
    mutable std::shared_timed_mutex m_flag_mtx;

    std::shared_ptr<NS_SKIDDETECTION::SkidDetection>  m_skid_detector_ptr;
};

#endif // _OPTICAL_SLIP_DETECTOR_H_hti