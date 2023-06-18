* [ ] 查找文件cpp/h的方法

```
#几种简化写法 对于多文件
# message(STATUS "（一）搜索文件所有需要编译的源文件打包编译")  
# file(GLOB_RECURSE H_SRCS *.h)  
# file(GLOB_RECURSE CXX_SRCS *.cpp)  #在项目中搜索所有cpp文件，build同时也会搜索
# file(GLOB_RECURSE NODE_SRCS "build/*.cpp")   
# file(GLOB_RECURSE EXAMPLE_SRCS "example/*.cpp")   
# list(REMOVE_ITEM CXX_SRCS ${NODE_SRCS})   #去掉build目录的 避免重定义
# list(REMOVE_ITEM CXX_SRCS ${EXAMPLE_SRCS})   #去掉example目录的 避免main重定义
# message(STATUS "头文件"   ${H_SRCS})  
# message(STATUS "源文件"   ${CXX_SRCS})  
```

* [ ] 查找规范第三方库的方法

```
#第三方库(查询是否安装：locate)
# PCL
#安装命令：sudo apt-get install libpcl-dev   
# find_package(PCL REQUIRED)
# include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})

#OpenCV
# find_package( OpenCV REQUIRED )  
```
