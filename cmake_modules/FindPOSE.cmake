#Try to find BAYES library
find_path(POSE_INCLUDE_DIRS NAMES pose.h PATHS /usr/local/include
											  /usr/include
											  /home/admins/project/SubstrateDevelopment/src/test_cmake_module/pose
											  ...)
#会在几个候选的PATHS中找到头文件并把正确的目录赋给BAYES_INCLUDE_DIR

find_library(POSE_LIBRARIES NAMES poselib PATHS /usr/local/include
												/usr/include
                                                /home/admins/project/SubstrateDevelopment/src/test_cmake_module/pose/build
												...)
#会在几个候选的PATHS中找到库文件并把完整的文件路径赋给BAYES_LIBRARIES
