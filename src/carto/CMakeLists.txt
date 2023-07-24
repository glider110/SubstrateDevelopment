include_directories(${PROJECT_SOURCE_DIR}/utils)
message(STATUS "path:" ${PROJECT_SOURCE_DIR}/utils )
aux_source_directory(${PROJECT_SOURCE_DIR}/utils  utils_src)
message(STATUS "源文件(不包括*.h):" ${utils_src})
add_executable(glog_test glog_test.cpp ${utils_src})
target_link_libraries(glog_test glog )   #glider note: 只需链接就行 头文件直接会在系统路径找

#memcpy 
add_executable(memcpy memcpy.cpp)

