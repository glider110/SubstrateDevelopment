set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

#测试小知识点
# add_executable(main_pcl  main.cpp)
# target_link_libraries(main_pcl   ${PCL_LIBRARIES} )#有没有后缀是



# add_executable(mesh_volmue  mesh_volmue.cpp)
# target_link_libraries(mesh_volmue   ${PCL_LIBRARIES} )#有没有后缀是

#滤波相关
# add_executable(passthrough  passthrough.cpp)
# target_link_libraries(passthrough   ${PCL_LIBRARIES} )#有没有后缀是


#三维重建
# add_executable(3d_reconstruction_tri  3d_reconstruction_tri.cpp)
# target_link_libraries(3d_reconstruction_tri   ${PCL_LIBRARIES} )#有没有后缀是


#分割相关


#平面凹凸包(点云投影)检测
# add_executable(hull_extraction  hull_extraction.cpp)
# target_link_libraries(hull_extraction   ${PCL_LIBRARIES} )#有没有后缀是


#随机采样一致性
# add_executable(random_sample_consensus  random_sample_consensus.cpp)
# target_link_libraries(random_sample_consensus   ${PCL_LIBRARIES} )#有没有后缀是


#kd&&octree
# add_executable(kd_oc_tree  kd_oc_tree.cpp)
# target_link_libraries(kd_oc_tree   ${PCL_LIBRARIES} )#有没有后缀是

#kd&&octree
add_executable(region_growing_segmentation  region_growing_segmentation.cpp)
target_link_libraries(region_growing_segmentation   ${PCL_LIBRARIES} )#有没有后缀是