cmake_minimum_required(VERSION 2.8)
project(demo)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake_modules/")
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../../cmake_modules/)   #和上面一句类似

find_package(POSE REQUIRED)  # POSE --> FindPOSE.cmake
include_directories(${POSE_INCLUDE_DIRS})
add_executable(demo main.cpp)
target_link_libraries(demo ${POSE_LIBRARIES})
