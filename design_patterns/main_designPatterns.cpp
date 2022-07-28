/*
 * @Author: glider
 * @Date: 2022-07-25 10:24:33
 * @LastEditTime: 2022-07-28 22:44:43
 * @FilePath: /SubstrateDevelopment/design_patterns/main_designPatterns.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <stdlib.h>
#include "Singleton.h"

int main(int argc, char const *argv[])
{
    Singleton::getinstance();
    return 0;
}
