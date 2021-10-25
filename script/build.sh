#!/bin/sh

# set -x
echo "#######################进入编译脚本###################"
SCRIPTPATH=$(readlink -f "$0")
PROJECTPATH=$(dirname $(dirname ${SCRIPTPATH}))
SOURCE_DIR=${PROJECTPATH}
BUILD_DIR=${PROJECTPATH}/build
RUN_DIR=${PROJECTPATH}/Release/bin
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install}
BUILD_NO_EXAMPLES=${BUILD_NO_EXAMPLES:-0}



USING_ROS=0

# if [ -d "$PROJECTPATH/build/" ];then
#         rm $PROJECTPATH/build/ -rf
#         echo "删除build"
# fi


echo ${INSTALL_DIR}
echo ${SOURCE_DIR}


if [ "$USING_ROS" = 0 ]
then
mkdir -p $BUILD_DIR\
  && cd $BUILD_DIR \
  && cmake  ..
  make
  cd   ${RUN_DIR}&& ./programmingtips
fi

echo "#######################编译结束！###################"
