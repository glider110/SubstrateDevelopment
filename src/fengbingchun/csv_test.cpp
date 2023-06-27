/*
 * @Author: glider
 * @Date: 2023-06-27 13:03:29
 * @LastEditTime: 2023-06-27 13:28:52
 * @FilePath: /SubstrateDevelopment/src/fengbingchun/csv_test.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include "csv.hpp"
#include  <vector>
#include <string>

void read_csv_test()
{
    using namespace std;
    vector<vector<double>> vec;
    vector<double> vec1{1,2,3};
    vector<double> vec2{4,5,6};
    vec.push_back(vec1);
    vec.push_back(vec2);
    string path("/home/admins/project/SubstrateDevelopment/data/writ.csv");
    NS_COMMON::csvWrite(vec,path);
}