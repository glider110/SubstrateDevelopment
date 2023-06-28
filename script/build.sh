#!/bin/sh
###
 # @Author: glider
 # @Date: 2023-06-18 15:56:52
 # @LastEditTime: 2023-06-28 19:02:32
 # @FilePath: /SubstrateDevelopment/script/build.sh
 # @Version:  v0.01
 # @Description: 
 # ************************************************************************
 # Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 # ************************************************************************
### 

# set -x
echo "#######################进入编译脚本......###################"


SCRIPTPATH=$(readlink -f "$0")
PROJECTPATH=$(dirname $(dirname ${SCRIPTPATH}))

if [ $PROJECTPATH = '/' ];then
   echo "usage: chmod a+x &&  ./build.sh or sh build.sh"
   exit
fi

usage() {
    echo "Usage:"
    echo "  ./build.sh [-p MACHINE MODEL] [-v debug or release]"
    echo "Description:"
    echo "    -p, 机型，当前可支持：x86、arm"
    echo "    -v, debug or release"
}

if [ ! $# -eq 4 ];then
    usage
    exit
fi
while getopts :p:v: option
do
   case "${option}"  in  
                p)
                    PLATFORM=${OPTARG}
                    ;;
                v) 
                    BUILD_TYPE=${OPTARG}
                    ;;
                ?) 
                    usage
                    exit
                    ;;
   esac
done

# 参数校验
if [ ! ${PLATFORM} = "x86" ] && 
   [ ! ${PLATFORM} = "arm" ]
then
    usage
    exit
fi

if [ ! ${BUILD_TYPE} = "release" ] && 
   [ ! ${BUILD_TYPE} = "debug" ]
then
    usage
    exit
fi

GLIDER_DEBUG=sss
SOURCE_DIR=${PROJECTPATH}
BUILD_DIR=${PROJECTPATH}/build


if [ -d "$BUILD_DIR" ];then
   rm $BUILD_DIR -rf
   echo "删除build"
fi
echo "#######################开始编译......###################"
mkdir -p $BUILD_DIR/$BUILD_TYPE \
  && cd $BUILD_DIR/$BUILD_TYPE

 echo $GLIDER_DEBUG 
 echo $BUILD_TYPE 
 echo $PLATFORM 
#使用场景 : 编译脚本传递参数 -> CMake脚本接收option -> 源代码宏(由外到里面传递)
cmake $SOURCE_DIR \
   -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
   -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
   -DPLATFORM=${PLATFORM} \

make
# make install  
echo "#######################编译结束！###################"
cd   ${PROJECTPATH}/release/x86/bin && ./cherno
# cd   ${PROJECTPATH}/release/x86/bin && ./glog_test
# cd   ${PROJECTPATH}/release/x86/bin && ./fbc

echo  "#######################运行结束！###################"