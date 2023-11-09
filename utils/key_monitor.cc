/*
 * @Author: glider
 * @Date: 2022-09-21 19:31:47
 * @LastEditTime: 2023-11-09 17:05:44
 * @FilePath: /SubstrateDevelopment/utils/key_monitor.cc
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include "key_monitor.h"

#include <sys/select.h>

namespace NS_KEY_MONITOR {

void KeyMonitor::init() {
    // 终端配置
    tcgetattr(0, &initial_settings);

    new_settings = initial_settings;

    new_settings.c_lflag &= ~ICANON;

    new_settings.c_lflag &= ~ECHO;

    new_settings.c_lflag &= ~ISIG;

    new_settings.c_cc[VMIN] = 1;

    new_settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &new_settings);

    // 后台启动
    thread_key_detect = std::thread(std::bind(&NS_KEY_MONITOR::KeyMonitor::key_detect_handle, this));
    thread_key_detect.detach();
}

bool KeyMonitor::get_monitor(char letter) {
    std::lock_guard<std::mutex> lock(mutex_letter);
    if (letter_detected == letter) {
        letter_detected = 0;
        return true;
    }
    return false;
}

void KeyMonitor::key_detect_handle() {
    int    ret;
    fd_set rfds;

    while (true) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);  // stdin

        ret = select(1, &rfds, nullptr, nullptr, nullptr);
        if (0 >= ret) {  // timeout or error
            continue;
        }

        if (FD_ISSET(0, &rfds)) {
            std::lock_guard<std::mutex> lock(mutex_letter);
            letter_detected = getchar();
        }
    }
}

}  // namespace NS_KEY_MONITOR
