# cherno实战练习
message(STATUS "===================================添加编译fliter scan=============================================")  

add_executable(cluster cluster.cpp )   


# install(TARGETS ${PROJECT_NAME}        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Release)   #执行 make  install(在发布版本时候用)
message(STATUS "===================================配置cherno完成=============================================")  
