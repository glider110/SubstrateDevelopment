#!bin/bash
###
 # @Author: glider
 # @Date: 2022-10-13 17:58:32
 # @LastEditTime: 2022-10-13 19:39:55
 # @FilePath: /SubstrateDevelopment/protobuf/build.sh
 # @Version:  v0.01
 # @Description: 
 # ************************************************************************
 # Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 # ************************************************************************
### 

protoc person.proto --cpp_out=. 

# 第一种编译方式:万金油
g++ write_person.cpp person.pb.cc person.pb.h -o write_person  -L /usr/local/lib  -lprotoc -lprotobuf
# 第一种编译方式:借助pkg_config,类似于cmake的findpackg #pkg-config --cflags --libs protobuf  参考https://blog.csdn.net/xt18971492243/article/details/123147573
# g++ write_person.cpp person.pb.cc person.pb.h -o write_person   -lprotobuf  -lpthread `pkg-config --cflags --libs protobuf`

g++ read_person.cpp person.pb.cc person.pb.h -o read_person  -L /usr/local/lib  -lprotoc -lprotobuf   &&

./write_person    &&
./read_person