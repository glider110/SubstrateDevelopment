cmake_minimum_required(VERSION 2.8)
project(ceres_demo)
# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) # 下面这种写法也可以
#include_directories(${OpenCV_DIRS})
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")

# add_executable(ceres_demo ceres_demo.cpp)
# target_link_libraries(ceres_demo ${CERES_LIBRARIES})

# add_executable(ceres_demo1 ceres_demo1.cpp)
# target_link_libraries(ceres_demo1 ${OpenCV_LIBS} ${CERES_LIBRARIES})

# add_executable(fit_demo curve_fitting_demo.cpp)
# target_link_libraries(fit_demo ${OpenCV_LIBS} ${CERES_LIBRARIES})

#手写高斯-牛顿迭代
# add_executable(gauss-newton gauss-newton.cpp)
# target_link_libraries(gauss-newton ${OpenCV_LIBS} ${CERES_LIBRARIES})

#凸优化
add_executable(convex_optimization convex_optimization.cpp)
target_link_libraries(convex_optimization ${CERES_LIBRARIES})

