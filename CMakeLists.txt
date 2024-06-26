#############################通用设置################################
message(STATUS "===================================进入顶层CmakeLists=============================================")  
cmake_minimum_required(VERSION 2.8)
project(baseproject)
set(CMAKE_CXX_STANDARD 11)

IF (PLATFORM  MATCHES "x86")
    SET(CROSSCOMPILE 0)
	SET(CMAKE_SYSTEM_PROCESSOR x86)
    message(STATUS " 编译平台: "   ${PLATFORM})            
ELSE()
	SET(CROSSCOMPILE 1)
	SET(CMAKE_SYSTEM_PROCESSOR aarch64)
    message(STATUS " 编译平台: "   ${PLATFORM})       
    #添加后续的工具链     
ENDIF()

#删除之前生成文件,避免未更新
FILE(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/sysroot/${CMAKE_SYSTEM_PROCESSOR})


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "release")
endif()

if( CMAKE_BUILD_TYPE MATCHES "debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -W  -std=c++14 -pthread -g") #-g 调试模式
    set(CMAKE_BUILD_TYPE debug)
    message(STATUS " 编译模式: "   ${CMAKE_BUILD_TYPE})            
else( CMAKE_BUILD_TYPE MATCHES "release" )
	IF(CROSSCOMPILE)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions -fpic -Wno-psabi -funwind-tables -finline-limit=64 -fsigned-char -no-canonical-prefixes -O3 -DNDEBUG")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W  -std=c++14 -O3")
	ELSE(CROSSCOMPILE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W  -std=c++14 -O3")
        message(STATUS " 编译模式: "   ${CMAKE_BUILD_TYPE})            
	ENDIF(CROSSCOMPILE)
endif( CMAKE_BUILD_TYPE MATCHES "debug" )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/release/${CMAKE_SYSTEM_PROCESSOR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/release/${CMAKE_SYSTEM_PROCESSOR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -W   -std=c++14 -pthread ")    #gdb调试时候是需要这句 -g

include_directories(utils)

#############################gtest单元测试#################################  
# add_subdirectory(third_party/googletest-release-1.10.0 )
# include_directories(third_party/googletest-release-1.10.0/googletest/include)

#############################生成编译文件#################################
####动静态库
add_subdirectory(example)         
# add_subdirectory(src/carto)                        #计算机视觉life:李想slam项目拆分
# add_subdirectory(src/std/sequent_structure)                 #类继承构造问题/定时器/按键获取等
# add_subdirectory(src/fengbingchun)                 #csdn:fengbingchun项目拆分
# add_subdirectory(src/cherno)                       #B站:c#csdn:herno C++课程
# add_subdirectory(src/dianyunxia)                   #csdn:点云侠pcl课程
# add_subdirectory(src/std/gtest)                      #gtest单元测试           
# add_subdirectory(src/gtest)                          #先依赖单元测试模块的库(先编译库)  gtest单元测试
# add_subdirectory(src/std/fliter_scan)                      #gtest单元测试           






#############################安装位置#################################(可以用install发布,也可以用release.sh脚本发布)
# install(TARGETS ${PROJECT_NAME}        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Release)   #执行 make  install(在发布版本时候用)
# set(CMAKE_INSTALL_BINDIR ${PROJECT_SOURCE_DIR}/debug/bin)
# set(CMAKE_INSTALL_LIBDIR ${PROJECT_SOURCE_DIR}/debug/lib)
# INSTALL(TARGETS cherno  utils
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
