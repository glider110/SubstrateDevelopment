cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(test_glogs)
 
SET(CMAKE_BUILD_TYPE Debug)
 
#glog
# include_directories(/data_2/lib/glog/include/)
# link_directories(/data_2/lib/glog/lib)

add_executable(glog_test glog_test.cpp)
target_link_libraries(glog_test glog utils)
# set_property(TARGET main PROPERTY CXX_STANDARD 11)
