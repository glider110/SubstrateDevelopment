/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-07-28 11:44:35
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-07-28 15:00:36
 * @FilePath: /SubstrateDevelopment/utils/tool.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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


/**
 * @brief: 执行shell命令
 * @param {string} &str
 * @result: 
 */
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








