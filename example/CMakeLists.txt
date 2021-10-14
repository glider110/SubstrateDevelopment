# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Release/lib) 
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})   #第三方库需要头文件 自定义的库的话没有要
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(chapter1  assignments_chapter1.cpp)
target_link_libraries(chapter1   ${PCL_LIBRARIES} )#有没有后缀是


add_executable(chapter2  assignments_chapter2.cpp)

