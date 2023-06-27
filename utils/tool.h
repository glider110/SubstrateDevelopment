/*
 * @Author: glider
 * @Date: 2022-09-21 19:31:47
 * @LastEditTime: 2023-06-28 00:17:52
 * @FilePath: /SubstrateDevelopment/utils/tool.h
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#ifndef _TOOL_H
#define _TOOL_H
// #pragma once

#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <sys/stat.h>

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

inline static uint64_t getSystemTimestampUS()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)(ts.tv_sec * 1e6 + ts.tv_nsec * 0.001);
}

inline bool IsExistFolder(const std::string& filePath)
{
    struct stat info;
    if (stat(filePath.c_str(), &info) != 0)
    {
        return false;
    }

    bool ret = (info.st_mode & S_IFDIR) != 0;
    if(!ret)
    {
        std::remove(filePath.c_str());
    }
    return ret;
}

inline std::string getCmdRes(const std::string &str)
{
    char result[1024] = {0};
    FILE *fp = popen(str.c_str(), "r"); // execute the shell command
    if (nullptr != fp)
    {
        fread(result, sizeof(char), sizeof(result), fp);
        pclose(fp);
        fp = nullptr;
    }
    else
    {
        return std::string("");
    }

    if (nullptr == result)
        return std::string("");

    return std::string(result); //result为字符串类型，atoi将字符串转化为int类型
}


#endif








