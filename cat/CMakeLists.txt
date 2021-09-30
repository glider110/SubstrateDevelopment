aux_source_directory(. CAT_SRCS)
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Release/lib) 
add_library(cat SHARED ${CAT_SRCS})

