cmake_minimum_required(VERSION 3.9.0)
# add_executable(${PROJECT_NAME})
file(GLOB_RECURSE header "*.h" "*.hpp")
file(GLOB_RECURSE source_cpp "*.cpp")
file(GLOB_RECURSE source_cu  "*.cu")
# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_cpp} ${header} ${source_cu})
# target_sources(${PROJECT_NAME} PRIVATE ${header} ${source_cpp} ${source_cu})
# set(CMAKE_CXX_STANDARD 11)

# if(WIN32)
# 	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CMAKE_CXX_FLAGS_DEBUG}  -O0 -Wall -g /Zi /Gm /INCREMENTAL")
# 	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall -g /Zi /INCREMENTAL")
# 	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF /INCREMENTAL")
# elseif(UNIX)
# 	set(CMAKE_CXX_VISIBILITY_PRESET hidden)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -O2 -Wall -g")
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -O2 -Wall -g")
# endif()

# list(APPEND CMAKE_MODULE_PATH "$ENV{LIBRARY_INSTALL_PATH}/share")

#cuda
# option(USE_CUDA "Use USE_CUDA support" ON)
# if(USE_CUDA)
# 	set(CUDA_PATH "$ENV{LIBRARY_INSTALL_PATH}/cuda")
# 	target_include_directories(${PROJECT_NAME} PUBLIC ${CUDA_PATH}/include) 
# 	target_link_directories(${PROJECT_NAME} PUBLIC ${CUDA_PATH}/lib/x64)
# 	file(GLOB CUDA_LIBRARIES "${CUDA_path}/lib/x64/*.lib")  #批量添加
# 	target_link_libraries(${PROJECT_NAME} PUBLIC ${CUDA_LIBRARIES})
# endif()

# #opencv
# option(USE_OPENCV "Use USE_OPENCV support" ON)
# if(USE_OPENCV)
# 	FIND_PACKAGE(OpenCV REQUIRED)
# 	if(OpenCV_FOUND)
# 		message(STATUS"OpenCV Found")
# 		target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
# 		target_link_directories(${PROJECT_NAME} PUBLIC ${OpenCV_LINK_DIRECTORIES})
# 		target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBRARIES})
# 	else()
# 		message(FATAL_ERROR"OpenCV Not Found!!!")
# 	endif()
# endif()

# #eigen
# option(USE_EIGEN "Use USE_EIGEN support" ON)
# if(USE_EIGEN)
# 	FIND_PACKAGE(Eigen3 REQUIRED)
# 	message(STATUS"Eigen Found ${EIGEN3_INCLUDE_DIR}")
# 	target_include_directories(${PROJECT_NAME} PUBLIC ${EIGEN3_INCLUDE_DIR})
# endif()

# #qhull
# option(USE_QHULL "Use USE_QHULL support" off)
# if(USE_QHULL)
# 	set(Qhull_DIR "$ENV{LIBRARY_INSTALL_PATH}/qhull_8_0_0/lib/cmake/Qhull")
# 	find_package(Qhull REQUIRED)
# 	if(Qhull_FOUND)
# 		message(STATUS"QHULL Found")
# 		target_include_directories(${PROJECT_NAME} PUBLIC ${QHULL_INCLUDE_DIRECTORIES})
# 		target_link_directories(${PROJECT_NAME} PUBLIC ${QHULL_LIBRARIES})
# 		target_compile_definitions(${PROJECT_NAME} PUBLIC ${QHULL_DEFINITIONS})
# 	else()
# 		message(FATAL_ERROR"QHULL Not Found!!!")
# 	endif()
# endif()

# #VTK
# option(USE_VTK "Use USE_VTK support" off)
# if(USE_VTK)
# 	set(VTK_DIR "$ENV{LIBRARY_INSTALL_PATH}/vtk_8_2_0/lib/cmake/vtk-8.2")
# 	find_package(VTK REQUIRED)
# 	if(VTK_FOUND)
# 		message(STATUS"VTK Found")
# 		target_include_directories(${PROJECT_NAME} PUBLIC ${VTK_USE_FILE})
# 	else()
# 		message(FATAL_ERROR"VTK Not Found!!!")
# 	endif()
# endif()

# #VTK
# option(USE_BOOST "Use USE_BOOST support" off)
# if(USE_BOOST)
# 	set(BOOST_ROOT "$ENV{LIBRARY_INSTALL_PATH}/boost_1_74_0")
# 	set(Boost_INCLUDE_DIR "$ENV{LIBRARY_INSTALL_PATH}/boost_1_74_0/include/boost-1_74")
# 	find_package(Boost 1.74.0 REQUIRED)
# 	if(Boost_FOUND)
# 		message(STATUS"BOOST Found")
# 		target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
# 		target_link_directories(${PROJECT_NAME} PUBLIC ${Boost_LIBRARY_DIRS})
# 		target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
# 	else()
# 		message(FATAL_ERROR"BOOST Not Found!!!")
# 	endif()
# endif()

# #PCL
# option(USE_PCL "Use USE_PCL support" off)
# if(USE_PCL)
# 	set(PCL_DIR  "$ENV{LIBRARY_INSTALL_PATH}/pcl_1_11_1/cmake")
# 	find_package(PCL REQUIRED)
# 	if(PCL_FOUND)
# 		message(STATUS"PCL Found")
# 		target_include_directories(${PROJECT_NAME} PUBLIC ${PCL_INCLUDE_DIRS})
# 		target_link_directories(${PROJECT_NAME} PUBLIC ${PCL_LIBRARY_DIRS})
# 		target_compile_definitions(${PROJECT_NAME} PUBLIC ${PCL_DEFINITIONS})
# 		target_link_libraries(${PROJECT_NAME} PUBLIC ${PCL_LIBRARIES})
# 	else()
# 		message(FATAL_ERROR"PCL Not Found!!!")
# 	endif()
# endif()

# PCL
#安装命令：sudo apt-get install libpcl-dev       
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})



####################################################
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../Release/bin/)    
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}) 
MESSAGE(${EXECUTABLE_OUTPUT_PATH} "==EXECUTABLE_OUTPUT_PATH==")
MESSAGE(${LIBRARY_OUTPUT_PATH} "==LIBRARY_OUTPUT_PATH==")

add_executable(${PROJECT_NAME}  ${source_cpp} ${header})
target_link_libraries(${PROJECT_NAME}   ${PCL_LIBRARIES})#有没有后缀是



MESSAGE(${CMAKE_CURRENT_SOURCE_DIR} "==CMAKE_CURRENT_SOURCE_DIR==")
MESSAGE(${CMAKE_C_COMPILER} "==CMAKE_C_COMPILER==")
