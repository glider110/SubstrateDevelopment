/*
 * @Author: glider
 * @Date: 2023-05-25 19:07:38
 * @LastEditTime: 2023-08-15 12:08:07
 * @FilePath: /SubstrateDevelopment/src/cherno/cherno_main.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <unistd.h>
#include "cherno.h"
// #include "../utils/ElapsedTimer.h"
#include "ElapsedTimer.h"     //没有这句include_directories() 编译器找不到路径
#include "timer.h"     //没有这句include_directories() 编译器找不到路径 
#include "singleton.hpp"
#include <vector>

#define PR_DEBUG 1 //可以在这里切换成0，作为一个开关
#if PR_DEBUG == 1   //如果PR_DEBUG为1
#define LOG(x)   std::cout << x <<std::endl     //简单的文本替换,不是具体函数,不需要入栈
#else
#define LOG(x)       //无文本替代,相当于没有log信息 用在调试时候
#endif

using namespace std;

// int s_v = 1;
extern int s_v;   //解释下 在函数内部的变量都是局部变量,包括main 只在本地scope可见


//模板是在编译时候预留,在调用定义<int>时才转换为代码
template<typename T>   
void printf_guo(T a){
    LOG(a);
}
//两个模板参数：类型和大小
template<typename T, int size>   //函数不行
class Array {    
private:
    T m_Array[size];
};


//测试if 和else if的小细节(互斥性)
void test1()
{
    int a = 5;
    if (a>1)
    {
       std::cout << "11111" << std::endl;
    }
    // if与else if的区别：就是if可以只要满足条件就执行，但是else if会发现即使第一个执行了，第二个满足条件依然不会执行。
    // 就像是一个互斥的现象。
    else if(a>2) std::cout << "22222" << std::endl;   
}

//pointer  reference 只是一个整数 表示地址的整数 类型无关
//区别 引用必须初始化 但不能赋值两次 它仅是alis别名本质是指针 
//那为啥不用指针呢 指针虽然可以赋值两次 但要解指针赋值较麻烦 所以看到定义函数参数时引用偏多些
void test2()
{   
    int a = 10;
    int b = 12;
    void* ptr_void;
    auto* ptr  = &a;   
    LOG(a);

    char* buffer = new char[8]; //返回一个8个字节的堆的第一个地址
    char** ptr1 = &buffer; //ptr是指向buffer所储存的地址的指针
    
    int& ref_a  = a;  // error: ‘ref_a’ declared as reference but not initialized   必须初始化
    // int& ref_a  = b;

}

//enum static
void test3()
{
    enum level{erro, warn,info};
    // LOG(info);
    LOG(s_v);
    extern int a;
    LOG(a);

}

//glider !:作用域与生命周期 时空
void test4()
{
    int a = 0;
    {
        a= 10;
        int b = 11;
        LOG(a);
    }
    //如果定义一个函数 加工上层的局部变量可以吗?
    // LOG(b);
    
}

//glider note:超级类测试用例
//基类析构函数如果没有virtual可能导致内存泄露,原因是子类虚构没有继承;
void test5()
{
    // AkAPI interface1;  //如果有纯虚函数就要报错,纯虚函数必须实例化子类
    // AkAPI* interface = new AkAPI();     //会报错，在这里我们必须给它一个实际上实现了这个函数的子类
    NS_CHERNO::AkAPI* interface = new NS_CHERNO::Entity();
    NS_CHERNO::Entity a;
    NS_CHERNO::AkAPI& interface_ref = a;
    delete interface;
    LOG("dddd");
}

//模板:解决重复编程问题
void test6()
{
printf_guo<int>(2);
printf_guo<std::string>("guoxiaofan");
Array<int, 5> array;
}

//短小精悍的综合运用(线程/指针/匿名函数/绑定)
void test7()
{
    auto lamda=[](int a){
        LOG("快速开辟线程...");
        LOG(a);
    };
    std::thread thread_test(lamda,10);
    thread_test.detach();
    std::make_shared<std::thread>(std::bind(lamda, 11))->detach();
    std::make_shared<std::thread>(std::bind(lamda, placeholders::_1),12)->detach();
    usleep(10);
}

//时间库chrono
void test8(){
    NS_COMMON::ElapsedTimer<int> a;
    sleep(1);
   LOG(a.elapsed());
   a.reset();
    sleep(2);
   LOG(a.elapsedSeconds());
   using namespace NS_COMMON;
   LOG(ToUniversal(GetCurrentTime()));
   a.reset();
   usleep(1000);
   LOG(a.elapsedMilliseconds());
   LOG(ToUniversal(GetCurrentTime()));
   LOG(GetCurrentDate());
//    LOG(::a);     glider ?:这个全局变量为啥不行
   LOG(::s_v);
}


//类型转换 对应69集
void test9(){
//to_string cstring
std::string a = "111";
const char* b = "222";
int c = 333;
//1.字母转数字
int d = atoi(a.c_str());
// int d = (int)a;
int f =std::stoi(a);
//2.数字转字母
string e = to_string(c);
string g = string(b);   //string构造

//glider: 强制装换
// int  h = static_cast<int>(a);
// int  h = static_cast<int>(b);
string  h = static_cast<string>(b);
// const char*  i = reinterpret_cast<const char*>(a);
}

//glider note: 测试单例
void test10()
{
    singleton::GetInstance()->print_ff();
}

/* //glider note: 左值右值/完美转发forward
// 【85】【Cherno C++】【中字】C++中的左值与右值
// 左值可以被称为地址值(在内存中有位置的实际变量)
// 右值可以被称为临时值(没有/访问不到存储空间、位置)
// 可以通过 常引用或者右值引用演唱右值的生命周期 
//和生命周期有关:static→一般变量→右值引到函数:拷贝/赋值/初始化列表
*/
void test11()
{
    // int& a = 10; 
    int&& b = 11;
    const int& c =12;
    // static int& d =12;
    //forward:生命周期的由于转换
    //move:降级生命周期
}

//stl
void test12()
{
    vector<int> a = {1, 2, 3};
    vector<int> b = {4,5,6,7,8,9};
    for( auto i :a){
        LOG(i);
    }
    a = b;
    for( auto i :a){
        LOG(i);
    }
}

int main()
{
    #ifdef GLIDERDEBUG1
    {
    LOG( "this is cherno test...");
    }
    test5();
    // std::cin.get();
    #endif
    test12();
}
int a = 111;   //全局区优先再编译时候处理,然后再找main 因此放在mian后面也能获取a的值