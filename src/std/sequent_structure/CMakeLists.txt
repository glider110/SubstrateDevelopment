# cherno实战练习
message(STATUS "===================================添加编译cherno=============================================")  

add_executable(no_para_structure no_para_structure.cpp )   
add_executable(para_structure para_structure.cpp )   
add_executable(thread_ptr thread_ptr.cpp )   
add_executable(func_timer func_timer.cpp )   



# install(TARGETS ${PROJECT_NAME}        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Release)   #执行 make  install(在发布版本时候用)
message(STATUS "===================================配置cherno完成=============================================")  
