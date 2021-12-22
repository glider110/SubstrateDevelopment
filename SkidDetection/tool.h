/*
 * @Author: your name
 * @Date: 2021-12-17 18:32:19
 * @LastEditTime: 2021-12-21 17:40:08
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /SubstrateDevelopment/SkidDetection/tool.h
 */
#ifndef _TOOL_H
#define _TOOL_H
// #pragma once

#include <string>
#include <iostream>
using namespace std;

inline void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


#endif