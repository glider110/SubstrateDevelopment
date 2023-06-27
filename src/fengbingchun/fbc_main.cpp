/*
 * @Author: glider
 * @Date: 2023-06-27 11:58:42
 * @LastEditTime: 2023-06-27 13:48:50
 * @FilePath: /SubstrateDevelopment/src/fengbingchun/fbc_main.cpp
 * @Version:  v0.01
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json11.hpp"
#include "funset.hpp"


int main()
{
	test4();
    read_csv_test();
    test_parse_cvs();
	std::cout << "ok" << std::endl;
	return 0;
}