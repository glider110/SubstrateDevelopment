cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)



# 添加测试目标
add_executable(UnitTests
    # base_point_cloud_process.cpp
    # base_point_cloud_process_test.cpp
    filter_box_test.cpp
)

# # 链接Google Test库
# target_link_libraries(UnitTests gtest_main gtest)
# # 添加Google Test库
# #find libgtest.so library
# find_library(GTEST 
#     gtest 
#     "/home/glider/project/glider_ws/SubstrateDevelopment/third_party/gtest" )
# find_library(GTEST_MAIN 
#     gtest_main 
#     "/home/glider/project/glider_ws/SubstrateDevelopment/third_party/gtest" )    
# IF (NOT GTEST)
#     MESSGAGE(FATAL_ERROR "libgtest.so not found")
# ENDIF(NOT GTEST)
# IF (NOT GTEST_MAIN)
#     MESSGAGE(FATAL_ERROR "libgtest_main.so not found")
# ENDIF(NOT GTEST_MAIN)
# message(STATUS " gtest path : " ${GTEST})
# message(STATUS " gtest_main path : " ${GTEST_MAIN})
target_link_libraries(UnitTests
    ${GTEST} 
    ${GTEST_MAIN})

link_directories(/home/glider/project/glider_ws/SubstrateDevelopment/release/x86/lib)

# target_link_libraries(UnitTests gtestd gtestd_main)
target_link_libraries(UnitTests gtest gtest_main)



# 添加测试
enable_testing()
add_test(NAME MyTests COMMAND UnitTests)