/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-07-06 16:36:17
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-07-26 13:53:36
 * @FilePath: /SubstrateDevelopment/carto/glog_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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
