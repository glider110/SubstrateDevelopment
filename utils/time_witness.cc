#include "time_witness.h"


namespace NS_COMMON {

Time TimeWitness::StartRecord(void) {
    if(IsStarting_) {
        std::cout << "["<<name_<<"]:: "<<"The Witness of time has was activated!!!!!" <<std::endl;
        std::cout << "["<<name_<<"]:: "<< "Please comfirm the witness of time is deactivated before activate time witness" << std::endl;
        return std::chrono::system_clock::now();
    }
    std::cout << "["<<name_<<"]:: "<< "The Witness of time is activated."<<std::endl;
    IsStarting_ = true;
    start_time_ = std::chrono::system_clock::now();
    return start_time_;
}

Time TimeWitness::StopRecord(void) {
    if(!IsStarting_) {
        std::cout << "["<<name_<<"]:: "<< "The Witness of time was not activated" <<std::endl;
        return std::chrono::system_clock::now();
    }
    else{
        stop_time_ = std::chrono::system_clock::now();
    }
    IsStarting_ = false;
    std::cout << "["<<name_<<"]:: "<< "The Witness of time was deactivated"<<std::endl;
    return stop_time_;
}

Time TimeWitness::StopRecord(double &time_ms) {
    if(!IsStarting_) {
        std::cout << "["<<name_<<"]:: "<< "The Witness of time was not activated"<<std::endl;
        return std::chrono::system_clock::now();
    }
    else{
        stop_time_ = std::chrono::system_clock::now();
    }
    IsStarting_ = false;
    std::chrono::duration<double> elapsed_seconds = stop_time_ - start_time_;
    time_ms = elapsed_seconds.count()*1000;
    std::cout << "["<<name_<<"]:: "<< "The Witness of time was deactivated"<<std::endl;
    return stop_time_;
}

double TimeWitness::msTimePasses(void) {
    Time pause_time_;
    if(!IsStarting_) {
        std::cout << "["<<name_<<"]:: "<< "The Witness of time was not activated"<<std::endl;
        return 0;
    }
    else {
        pause_time_ = std::chrono::system_clock::now();
    }
    std::chrono::duration<double> elapsed_seconds = pause_time_ - start_time_;
    return elapsed_seconds.count()*1000;
} 

} // namespace NS_COMMON

