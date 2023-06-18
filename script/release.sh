#!/bin/sh

SCRIPTPATH=$(readlink -f "$0")
PROJECTPATH=$(dirname $(dirname ${SCRIPTPATH}))

# bms 生成的动态库
SRC_ARM_LIB_PATH=${PROJECTPATH}/Release/aarch64/lib

# bms 进程
SRC_EXE_PATH=${PROJECTPATH}/Release/aarch64/bin/bms_svc

# bms 所需配置文件
SRC_CONFIG_PATH=${PROJECTPATH}/config

# tof内部公用库的路径
DEST_PUBLIC_REPOSITORY_LIB=${PROJECTPATH}/../pcl_library/lib
DEST_PUBLIC_REPOSITORY_CONFIG=${PROJECTPATH}/../pcl_library/config
DEST_PUBLIC_REPOSITORY_EXE=${PROJECTPATH}/../pcl_library/exe

echo "Sync includes and libs to public repository..."
cp  -r ${SRC_ARM_LIB_PATH}/*         ${DEST_PUBLIC_REPOSITORY_LIB}/aarch64   &&
cp  -r ${SRC_CONFIG_PATH}/*      ${DEST_PUBLIC_REPOSITORY_CONFIG}   &&
cp  -r ${SRC_EXE_PATH}           ${DEST_PUBLIC_REPOSITORY_EXE}   &&

echo "Sync finished."