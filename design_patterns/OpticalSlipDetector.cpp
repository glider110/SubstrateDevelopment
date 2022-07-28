/*
 * @Author: glider
 * @Date: 2022-07-28 16:08:23
 * @LastEditTime: 2022-07-28 22:40:11
 * @FilePath: /SubstrateDevelopment/design_patterns/OpticalSlipDetector.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */



#include "OpticalSlipDetector.h"

#include "sleep_timer.h"


OpticalSlipDetectorPtr OpticalSlipDetector::getInstance(
    AKShareQueue<FrameBufQueue> *cam_data_queue_ptr,
    ThreadPool *pool_ptr)
{
    static OpticalSlipDetectorPtr instance{new OpticalSlipDetector(cam_data_queue_ptr, pool_ptr)};
    return instance;
}

OpticalSlipDetector::OpticalSlipDetector(AKShareQueue<FrameBufQueue> *cam_data_queue_ptr,
                                         ThreadPool *pool_ptr)
    : m_cam_data_queue_ptr(cam_data_queue_ptr),
      m_pool_ptr(pool_ptr)
{
    m_run = false;
    m_need_stop = false;
    m_new_cam_ptr = nullptr;
    m_new_pose_ptr = nullptr;
    clearDetectFlag();

    //保存log
    if(1)
    {
        string save_data_path ="/tmp/glider/";
        string save_data_path_image ="/tmp/glider/image/";
        if (!IsExistFolder(save_data_path))
        {
            int ret = mkdir(save_data_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        else
        {
            string cmdStr = "rm -rf " + save_data_path + "/* ";
            string result = getCmdRes(cmdStr);
        }
        if (!IsExistFolder(save_data_path_image))
        {
            int ret_imag = mkdir(save_data_path_image.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        else
        {
            string cmdStr_image = "rm -rf " + save_data_path_image + "/* ";
            string result_image = getCmdRes(cmdStr_image);
        }
    }
 
    m_skid_detector_ptr = std::make_shared<NS_SKIDDETECTION::SkidDetection>();

}

OpticalSlipDetector::~OpticalSlipDetector()
{
    stopDetect();
}

void OpticalSlipDetector::clearDetectFlag()
{
    m_new_cam_ptr = &m_cam_buf1;
    m_new_pose_ptr = &m_pose_buf1;
    
    SlipInputData null_data{nullptr, nullptr};
    m_last_input = null_data;
    m_cur_input = null_data;

    std::lock_guard<shared_timed_mutex> lock{m_flag_mtx};
    m_slip_flag.status = 1;
    m_slip_flag.timestamp = getSystemTimestampUS() / 1000;
}

void OpticalSlipDetector::detecting()
{
    static std::mutex thread_mtx;
    std::lock_guard<std::mutex> thread_lock{thread_mtx};

    // {
    //     std::lock_guard<std::mutex> lock{m_detect_mtx};
    //     m_need_stop = false;
    // }

    auto swapDataBuffer = [this]()
    {
        if (m_new_cam_ptr == nullptr)
            m_new_cam_ptr = &m_cam_buf1;
        else
            m_new_cam_ptr = m_new_cam_ptr == &m_cam_buf1 ? &m_cam_buf2 : &m_cam_buf1;

        if (m_new_pose_ptr == nullptr)
            m_new_pose_ptr = &m_pose_buf1;
        else
            m_new_pose_ptr = m_new_pose_ptr == &m_pose_buf1 ? &m_pose_buf2 : &m_pose_buf1;
    };

    auto printPtr = [this]()
    {
        // auto addr1 = &m_cam_buf1;
        // auto addr2 = &m_cam_buf2;

        // if (m_new_cam_ptr == nullptr)
        //     printf("[[ new_cam_ptr point to nullptr ]]\n");
        // else if (m_new_cam_ptr == addr1)
        //     printf("[[ new_cam_ptr point to data1 ]]\n");
        // else if (m_new_cam_ptr == addr2)
        //     printf("[[ new_cam_ptr point to data2 ]]\n");

        // if (m_last_input.first == nullptr)
        //     printf("[[ last_cam_ptr point to nullptr ]]\n");
        // else if (m_last_input.first == addr1)
        //     printf("[[ last_cam_ptr point to data1 ]]\n");
        // else if (m_last_input.first == addr2)
        //     printf("[[ last_cam_ptr point to data2 ]]\n");

        // if (m_cur_input.first == nullptr)
        //     printf("[[ cur_cam_ptr point to nullptr ]]\n");
        // else if (m_cur_input.first == addr1)
        //     printf("[[ cur_cam_ptr point to data1 ]]\n");
        // else if (m_cur_input.first == addr2)
        //     printf("[[ cur_cam_ptr point to data2 ]]\n");
    };

    bool need_match_pose = false;
    SleepTimer t{20.0f};
    while (true)
    {
        std::unique_lock<std::mutex> run_lock{m_detect_mtx};
        if (m_need_stop)
        {
            m_need_stop = false;
            m_run = false;
            break;
        }
        run_lock.unlock();

        auto cur_ts = getSystemTimestampUS() / 1000;

        // drill all pose in queue and add to list and remove data 500ms away from now
        std::unique_lock<std::mutex> feed_lock{m_feed_mtx};
        // printf("cur ts = %llu, pose_queue = %llu\n", cur_ts, m_pose_queue.size());
        while (!m_pose_queue.empty())
        {
            // printf("pose data ts = %llu\n", m_pose_queue.front().timestamp);
            m_pose_data.emplace_back(m_pose_queue.front());
            m_pose_queue.pop();
        }
        feed_lock.unlock();

        while (!m_pose_data.empty())
        {
            auto ts_diff = cur_ts - m_pose_data.front().timestamp;
            if (ts_diff > 500)
                m_pose_data.pop_front();
            else
                break;
        }

        // printf("pose data size = %llu\n", m_pose_data.size());

        do
        {
            if (m_new_cam_ptr == nullptr || m_new_pose_ptr == nullptr)
            {
                swapDataBuffer();
                printPtr();
            }

            // get new cam frame
            bool cam_data_updated = false;
            cam_data_updated = m_cam_data_queue_ptr->dequeue(m_new_cam_ptr);
            if (cam_data_updated)
            {
                need_match_pose = true;
                // printf("cam data updated, cam data ts = %llu\n", m_new_cam_ptr->timestamp / 1000);
            }

            if (!need_match_pose)
                break;

            // match cam frame and pose data
            auto new_cam_ts = m_new_cam_ptr->timestamp / 1000;
            bool match_success = false; 
            for (auto &pose_data : m_pose_data)
            {
                auto pose_ts = pose_data.timestamp;
                if (pose_ts >= new_cam_ts && pose_ts - new_cam_ts <= 15)
                {
                    *m_new_pose_ptr = pose_data;
                    match_success = true;
                    // printf("match success, pose data ts = %llu\n", m_new_pose_ptr->timestamp);
                    break;
                }
            }

            if (!match_success)
                break;
            else
                need_match_pose = false;

            if (m_last_input.first == nullptr || m_last_input.second == nullptr)
            {
                // no last input data
                printPtr();
                // printf("no last input data\n");
                m_last_input.first = m_new_cam_ptr;
                m_last_input.second = m_new_pose_ptr;
                swapDataBuffer();
                printPtr();
            }
            else
            {
                printPtr();
                m_cur_input.first = m_new_cam_ptr;
                m_cur_input.second = m_new_pose_ptr;

                auto last_cam_ts = m_last_input.first->timestamp / 1000;
                auto cur_cam_ts = m_cur_input.first->timestamp / 1000;
                // check if 2 cam frames time interval large then 250

                // printf("cur_cam_ts = %llu, last_cam_ts = %llu\n", cur_cam_ts, last_cam_ts);
                if (cur_cam_ts >= last_cam_ts && cur_cam_ts - last_cam_ts >= 450)
                {
                    // printf("cam ts diff > 250, do detection\n");
                    swapDataBuffer();
                    printPtr();

                    // do skid detect
                    m_skid_detector_ptr->input(*m_last_input.second, *m_last_input.first,
                        *m_cur_input.second, *m_cur_input.first);
                    m_skid_detector_ptr->record_data();
                    m_skid_detector_ptr->detect_dense();

                    // set result to slip flag
                    std::unique_lock<shared_timed_mutex> lock{m_flag_mtx};
                    m_slip_flag.status = m_skid_detector_ptr->get_status();
                    m_slip_flag.timestamp = m_cur_input.first->timestamp / 1000;
                    lock.unlock();

                    m_last_input.first = m_cur_input.first;
                    m_last_input.second = m_cur_input.second;
                    printPtr();
                }
                else
                {
                    // discard this frame, do nothing
                    // printf("ignore cur cam frame\n");
                    printPtr();
                }
            }
        } while (0);

        t.sleep();
    }
}

bool OpticalSlipDetector::startDetect()
{
    std::lock_guard<std::mutex> lock{m_detect_mtx};
    if (!m_run || (m_need_stop && m_run))
    {
        m_pool_ptr->enqueue([&]() { detecting(); });
        m_run = true;
    }

    return true;
}

void OpticalSlipDetector::stopDetect()
{
    std::lock_guard<std::mutex> lock{m_detect_mtx};
    if (m_run)
        m_need_stop = true;
}

void OpticalSlipDetector::feedPoseData(const PlanData &pose_data)
{
    std::lock_guard<std::mutex> lock{m_feed_mtx};
    if (m_pose_queue.size() < 4)
    {
        m_pose_queue.push(pose_data);
    }
    else
    {
        m_pose_queue.pop();
        if (m_pose_queue.size() < 4)
            m_pose_queue.push(pose_data);
    }
    // printf("pose queue size = %llu\n", m_pose_queue.size());
}

SlipData OpticalSlipDetector::getFlag() const
{
    std::lock_guard<shared_timed_mutex> lock{m_flag_mtx};
    return m_slip_flag;
}
