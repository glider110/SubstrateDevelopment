/*
 * @Author: glider
 * @Date: 2022-07-29 10:25:48
 * @LastEditTime: 2022-08-15 14:44:01
 * @FilePath: /SubstrateDevelopment/utils/tool.h
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
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

namespace NA_TOOL
{
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

/**
 * @description: 
 * @param {string&} filePath
 * @return {*}
 */
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


inline void mkDir(const string& save_data_path)
{
    // string save_data_path ="/tmp/glider/image/";
    if (!IsExistFolder(save_data_path))
    {
        int ret = mkdir(save_data_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    else
    {
        string cmdStr = "rm -rf " + save_data_path + "/* ";
        string result = getCmdRes(cmdStr);
    }
}


/**
 * @description: 
 * @param {string}  &pathname
 * @param {string} &data
 * @return {*}
 */
bool WriteFile(const std::string &pathname, const std::string &data) {
    std::fstream fs;
    fs.open(pathname, std::ios_base::out);
    if (false == fs.is_open()) {
        return false;
    }

    fs.write(data.data(), data.size());
    fs.close();
}

} // namespace name
#endif








