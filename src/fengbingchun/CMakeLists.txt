# fengbingchun实战练习
message(STATUS "===================================添加编译fbc=============================================")  
message(STATUS " 项目路径:"   ${PROJECT_SOURCE_DIR})                                     #今后小工具库都按照这种形式添加,不需要先编译为库,方便理解阅读
message(STATUS "当前路径:"   ${CMAKE_CURRENT_SOURCE_DIR})   
file(GLOB_RECURSE  H_SRCS  "${PROJECT_SOURCE_DIR}/utils/*.h")  
file(GLOB_RECURSE  HPP_SRCS  "${PROJECT_SOURCE_DIR}/utils/*.hpp")  
file(GLOB_RECURSE CXX_SRCS  "${PROJECT_SOURCE_DIR}/utils/*.cc"  "${PROJECT_SOURCE_DIR}/utils/*.cpp")  #
message(STATUS "utils头文件:"   ${H_SRCS})   
message(STATUS "utils头文件(hpp):"   ${HPP_SRCS})   
message(STATUS "utils源文件:"   ${CXX_SRCS})  
set(utils_src ${H_SRCS}  ${CXX_SRCS} ${HPP_SRCS})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} fbc_src)
include_directories(${PROJECT_SOURCE_DIR}/utils/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(fbc  ${fbc_src}  ${utils_src})   
# add_definitions(-DGLIDERDEBUG=1)
target_compile_definitions(fbc PUBLIC -DGLIDERDEBUG1)   #和上面一样,尽量用define 而不是用option
target_link_libraries(fbc glog)


# install(TARGETS ${PROJECT_NAME}        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Release)   #执行 make  install(在发布版本时候用)
message(STATUS "===================================配置cherno完成=============================================")  
