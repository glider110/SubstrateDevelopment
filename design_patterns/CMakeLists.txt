aux_source_directory(. design_patterns)
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Release/lib) 
# add_library(cat SHARED ${CAT_SRCS})
add_executable(main_designPatterns main_designPatterns.cpp Singleton.h)

