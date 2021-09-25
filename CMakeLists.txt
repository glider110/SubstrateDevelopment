cmake_minimum_required(VERSION 2.8)

project(baseproject)

# enable_testing()

ADD_DEFINITIONS(-D GLOG_NO_ABBREVIATED_SEVERITIES)

if(USING_OF MATCHES 1)
  message("USING OLD OFILM MODULE" )
  add_definitions(-DUSING_OF)
elseif(USING_OF MATCHES 2)  
  message("USING NEW OFILM MODULE" )
  add_definitions(-DUSING_OF_NEW)
else()
  message("USING SUNNY MODULE" )
  add_definitions(-DUSING_SUNNY)
endif() 

if(USING_RK3326)
  add_definitions(-DUSING_RK3326)
endif() 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

IF(CROSSCOMPILE)
	INCLUDE(CMakeForceCompiler)
	set(CMAKE_SYSTEM_NAME Linux)

	# RK3399 ###############################################
	set(COMPILER_DIR /opt/rockchip-cc-tools/host/usr)
    set(CMAKE_FIND_ROOT_PATH ${COMPILER_DIR}/aarch64-rockchip-linux-gnu/sysroot)
    set(CMAKE_C_COMPILER ${COMPILER_DIR}/bin/aarch64-linux-gcc)
    set(CMAKE_CXX_COMPILER ${COMPILER_DIR}/bin/aarch64-linux-g++)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)

	SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
	SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
	#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/bin/)
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/lib/)
else()
	#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/bin/)
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/lib/)
ENDIF()

if( CMAKE_BUILD_TYPE MATCHES "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall  -std=c++14 -pthread -g")
else( CMAKE_BUILD_TYPE MATCHES "Release" )
	IF(CROSSCOMPILE)
		# RK3399 ###############################################
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions -fpic -Wno-psabi -funwind-tables -finline-limit=64 -fsigned-char -no-canonical-prefixes -O3 -DNDEBUG  -DNDEBUG")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -std=c++14 -O3")
		# R16 ##################################################
		# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions -fpic -Wno-psabi -funwind-tables -finline-limit=64 -fsigned-char -no-canonical-prefixes -march=armv7-a -mfloat-abi=hard -mhard-float -mfpu=neon -O3 -DNDEBUG  -DNDEBUG")
		# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -std=c++11 -O3 -march=armv7-a -mfloat-abi=hard -mhard-float -mfpu=neon")
	ELSE(CROSSCOMPILE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -std=c++14 -O3")
	ENDIF(CROSSCOMPILE)
endif( CMAKE_BUILD_TYPE MATCHES "Debug" )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Release/${CMAKE_SYSTEM_PROCESSOR}/lib)

include_directories(
	${PROJECT_SOURCE_DIR}/3rdparty/include/
	${PROJECT_SOURCE_DIR}/tof/
	${PROJECT_SOURCE_DIR}/../k900/include/cms/
	${PROJECT_SOURCE_DIR}/include/
	${PROJECT_SOURCE_DIR}/include/msg/
	${PROJECT_SOURCE_DIR}/include/aktof
	${PROJECT_SOURCE_DIR}/../library/include/

)

IF(CROSSCOMPILE)
if(USING_OF MATCHES 2)	
	link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib_of_new)
elseif(USING_OF MATCHES 1)
	link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib_of)
else()
	link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib)
endif()
ENDIF(CROSSCOMPILE)

link_directories(
	${LIBRARY_OUTPUT_PATH}
	${CMAKE_FIND_ROOT_PATH}/usr/lib
	${PROJECT_SOURCE_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR}	
	${PROJECT_SOURCE_DIR}/../library/libs/${CMAKE_SYSTEM_PROCESSOR}	
)

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})


IF(CROSSCOMPILE)
	link_directories(
		${PROJECT_SOURCE_DIR}/../k900/lib/${CMAKE_SYSTEM_PROCESSOR}
	)
	add_subdirectory(tof)
	add_subdirectory(bms_service)
	add_subdirectory(Examples)
ELSE(CROSSCOMPILE)
	include_directories(
		${PROJECT_SOURCE_DIR}/../library/ocv_341/include
		${PROJECT_SOURCE_DIR}/../library/ocv_341/include/opencv2
	)
	link_directories(
		${PROJECT_SOURCE_DIR}/../library/ocv_341/libs/${CMAKE_SYSTEM_PROCESSOR}
	)
	add_subdirectory(Examples)
ENDIF(CROSSCOMPILE)