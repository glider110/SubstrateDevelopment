
cmake_minimum_required(VERSION 2.8)
project(baseproject)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -W  -std=c++14 -pthread ")    #gdb调试时候是需要这句 -g
set(CMAKE_BUILD_TYPE "Release")
#############################预先设置################################
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Release/lib) 
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Release/bin) 
#几种简化写法 对于多文件
message(STATUS "（一）搜索文件所有需要编译的源文件打包编译")  
file(GLOB_RECURSE H_SRCS *.h)  
file(GLOB_RECURSE CXX_SRCS *.cpp)  #在项目中搜索所有cpp文件，build同时也会搜索
file(GLOB_RECURSE NODE_SRCS "build/*.cpp")   
file(GLOB_RECURSE EXAMPLE_SRCS "example/*.cpp")   
list(REMOVE_ITEM CXX_SRCS ${NODE_SRCS})   #去掉build目录的 避免重定义
list(REMOVE_ITEM CXX_SRCS ${EXAMPLE_SRCS})   #去掉example目录的 避免main重定义
message(STATUS "头文件"   ${H_SRCS})  
message(STATUS "源文件"   ${CXX_SRCS})  

message(STATUS "（二）设置全部已经编译好的库为一个变量")  
set(ALL_LIBRARY cat person)
message(STATUS "库文件"   ${ALL_LIBRARY})  
# 自定义库(cmake机制 自定义的库不需要link_directories)   
link_directories(${PROJECT_SOURCE_DIR}/Release/lib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/cat/)


#第三方库(查询是否安装：locate)
# PCL
#安装命令：sudo apt-get install libpcl-dev       
# find_package(PCL REQUIRED)
# include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})

#OpenCV
# find_package( OpenCV REQUIRED )  






#############################生成编译文件#################################
####动静态库
# add_library( person SHARED  src/person.cpp)
# # add_library(cat cat/cat.cpp)
# add_subdirectory(cat )  
add_subdirectory(example)  

####可执行文件
##1.纯源码
# add_executable(main  ${CXX_SRCS}  )
##1.链接动态库
# add_executable(main main.cpp  )
# target_link_libraries(main cat person 	${OpenCV_LIBS} ${PCL_LIBRARIES} )#有没有后缀是
# target_link_libraries(main cat person  )#有没有后缀是
#############################安装位置#################################