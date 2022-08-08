/*
 * @Author: glider
 * @Date: 2022-07-29 10:25:48
 * @LastEditTime: 2022-08-01 14:08:47
 * @FilePath: /SubstrateDevelopment/carto/memcpy.cpp
 * @Version:  v0.01
 * @Description:  测试memcopy函数
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */


#include <string>
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char** argv){

    std::string src = "this is test";
    std::string dest;

    cout << "after memcpy src :" << src <<endl;
    cout << "after memcpy dest :" << dest <<endl;

    memcpy(&dest, &src ,sizeof(src));
    cout << "after memcpy dest :" <<  dest <<endl;
    cout << "after memcpy src :" <<  src <<endl;


    std::cout<<"-------end-----"<<std::endl;
    return 0;
}
