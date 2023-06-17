aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SRCS)
set(COMMON_SRCS_LIST ${DIR_SRCS}  CACHE INTERNAL "")
add_library(utils SHARED ${DIR_SRCS})
message(STATUS "utils全部文件:"   ${DIR_SRCS})     #只输出cpp文件
