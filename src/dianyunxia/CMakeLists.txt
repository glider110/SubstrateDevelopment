
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(mesh_volmue  mesh_volmue.cpp)
target_link_libraries(mesh_volmue   ${PCL_LIBRARIES} )#有没有后缀是


