#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termio.h>
#include <unistd.h>
#include <cstring>

#include "manual_ctrl.h"


namespace NS_MANUAL {

ControlKey::ControlKey()
    :  last_key_{0} {}

void ControlKey::enter_key_monitor() {
    PrintUsage();  // 打印使用说明

    system("stty -echo");  // 关闭回显

    SetKeyboardAttr();

    // 非后台启动
    // key_detect_handle();    
    // 后台启动
    thread_key_detect = std::thread(std::bind(&NS_MANUAL::ControlKey::key_detect_handle, this));
    thread_key_detect.detach();
}


bool ControlKey::get_monitor(char letter) {
    // std::lock_guard<std::mutex> lock(mutex_letter);
    if (last_key_ == letter) {
        last_key_ = 0;
          std::cout << "\nxxxxxxxxxxxx:" << last_key_<<std::endl;
        return true;
    }
    return false;
}


void ControlKey::SetKeyboardAttr() {
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);  // 按键按下后不用敲回车
}

int ControlKey::ScanKeyboard() {
    return getchar();
}

void ControlKey::PrintUsage() {
    std::cout << "\nManual Usage:\n"
                 "  w  : go forward\n"
                 "  s  : go backward\n"
                 "  a  : turn left\n"
                 "  d  : turn right\n"
                 "space: stop\n";
}


void ControlKey::key_detect_handle() {
    int            ret;
    int            key;
    fd_set         rfds;
    struct timeval tv;
    while (true) {
        tv.tv_sec  = 0;           // seconds
        tv.tv_usec = 500 * 1000;  // microseconds

        FD_ZERO(&rfds);
        FD_SET(0, &rfds);  // stdin

        ret = select(1, &rfds, nullptr, nullptr, &tv);
        if (0 > ret) {
            char reason[256];
            std::cout << "select error, reason=%s" << strerror_r(errno, reason, sizeof(reason)) << std::endl;
            return;
        }

        if (FD_ISSET(0, &rfds)) {
            key = ScanKeyboard();
            // HandleKey(key);
            last_key_ = key;
            //  std::cout << "\nManual Usage:" << last_key_<<std::endl;
        }
    }
}

}  // namespace NS_MANUAL

