# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Release/lib) 
# find_package(PCL REQUIRED)
# include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})
# OpenCV
# find_package( OpenCV REQUIRED )  

# add_executable(demo_data_structure  demo_data_structure.cpp)
# target_link_libraries(demo_data_structure  	${OpenCV_LIBS} ${PCL_LIBRARIES})#有没有后缀是

# add_executable(chapter1  assignments_chapter1.cpp)
# target_link_libraries(chapter1   ${PCL_LIBRARIES} )#有没有后缀是

# add_executable(eigen_test  eigen_test.cpp)

# #新特性测试
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




# cherno实战练习
message(STATUS "===================================添加编译cherno=============================================")  
message(STATUS " 项目路径:"   ${PROJECT_SOURCE_DIR})                                     #今后小工具库都按照这种形式添加,不需要先编译为库,方便理解阅读
message(STATUS "当前路径:"   ${CMAKE_CURRENT_SOURCE_DIR})   
file(GLOB_RECURSE  H_SRCS  "${PROJECT_SOURCE_DIR}/utils/*.h")  
file(GLOB_RECURSE CXX_SRCS  "${PROJECT_SOURCE_DIR}/utils/*.cc")  #
message(STATUS "utils头文件:"   ${H_SRCS})   
message(STATUS "utils源文件:"   ${CXX_SRCS})  
set(utils_src ${H_SRCS}  ${CXX_SRCS})
set(chero_src cherno_main.cpp cherno.h)
include_directories(${PROJECT_SOURCE_DIR}/utils/)
add_executable(cherno  ${chero_src}  ${utils_src})
# install(TARGETS ${PROJECT_NAME}        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Release)   #执行 make  install(在发布版本时候用)
message(STATUS "===================================配置cherno完成=============================================")  
