#!/bin/sh
###
 # @Author: your name
 # @Date: 2021-09-30 14:32:05
 # @LastEditTime: 2021-12-17 13:45:32
 # @LastEditors: Please set LastEditors
 # @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 # @FilePath: /SubstrateDevelopment/script/build.sh
### 

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

if [ -d "$PROJECTPATH/build/" ];then
        rm $PROJECTPATH/build/ -rf
        echo "删除build"
fi


echo ${INSTALL_DIR}
echo ${SOURCE_DIR}

echo "#######################开始编译......###################"
if [ "$USING_ROS" = 0 ]
then
mkdir -p $BUILD_DIR\
  && cd $BUILD_DIR \
  && cmake  ..
  make
  echo "#######################编译结束！###################"
  cd   ${RUN_DIR}&& ./demo_data_structure  
#   cd   ${RUN_DIR}&& ./carto_test  
#   cd   ${RUN_DIR}&& ./lider_trans  
fi

echo "#######################运行结束！###################"
