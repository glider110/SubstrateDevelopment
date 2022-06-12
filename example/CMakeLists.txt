# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Release/lib) 
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# OpenCV
find_package( OpenCV REQUIRED )  

add_executable(demo_data_structure  demo_data_structure.cpp)
target_link_libraries(demo_data_structure  	${OpenCV_LIBS} ${PCL_LIBRARIES})#有没有后缀是

# add_executable(chapter1  assignments_chapter1.cpp)
# target_link_libraries(chapter1   ${PCL_LIBRARIES} )#有没有后缀是

# add_executable(chapter2  assignments_chapter2.cpp)

#新特性测试
# add_executable(programmingtips demo_programmingtips.cpp)
# add_executable(demo_thread demo_thread.cpp)

# add_executable(registration  demo_registration.cpp)
# target_link_libraries(registration   ${PCL_LIBRARIES} )#有没有后缀是

#光流
# add_executable(opticlflow  demo_opticlflow.cpp)
# target_link_libraries(opticlflow  	${OpenCV_LIBS} )

#点云配准模块
# aux_source_directory(../tofLocation var_toflocation)
# aux_source_directory(../SkidDetection var_SkidDetection)
# add_executable(test_main  test_main.cpp  ${var_SkidDetection})
# target_link_libraries(test_main  	${OpenCV_LIBS} ${PCL_LIBRARIES})



#激光雷达坐标变换
# add_executable(lider_trans  lider_trans.cpp)
# target_link_libraries(lider_trans  	)#有没有后缀是

# carto代码编程技巧
# add_executable(carto_test  carto_test.cpp)
# target_link_libraries(carto_test  	)#有没有后缀是