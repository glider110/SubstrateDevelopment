cmake_minimum_required(VERSION 2.8)
project(ceres_demo)
# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # 下面这种写法也可以
#include_directories(${OpenCV_DIRS})
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

add_executable(ceres_demo ceres_demo.cpp)
target_link_libraries(ceres_demo ${CERES_LIBRARIES})

add_executable(fit_demo curve_fitting_demo.cpp)
target_link_libraries(fit_demo ${OpenCV_LIBS} ${CERES_LIBRARIES})



# cmake_minimum_required(VERSION 2.8)
# project(fit_demo)

# # opencv
# find_package(OpenCV REQUIRED)

# include_directories(${OpenCV_INCLUDE_DIRS}) # 下面这种写法也可以
# #include_directories(${OpenCV_DIRS})

# # ceres
# find_package(Ceres REQUIRED)
# include_directories(${CERES_INCLUDE_DIRS})

# add_executable(fit_demo curve_fitting_demo.cpp)
# target_link_libraries(fit_demo ${OpenCV_LIBS} ${CERES_LIBRARIES})
