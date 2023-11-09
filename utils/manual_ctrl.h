#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>

namespace NS_MANUAL {

class ControlKey {
public:
    ControlKey();

    void enter_key_monitor();
    bool get_monitor(char letter);

private:


    void SetKeyboardAttr();
    void key_detect_handle();
    void PrintUsage();

    int   last_key_;
    int  ScanKeyboard();
    std::thread thread_key_detect;
};

}  // namespace NS_MANUAL

