/*
 * @Author: glider
 * @Date: 2023-05-25 19:07:38
 * @LastEditTime: 2023-06-13 23:34:15
 * @FilePath: /SubstrateDevelopment/example/cherno_main.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
// #include "cherno.cpp"
#define LOG(x)   std::cout << x <<std::endl


// int s_v = 1;
extern int s_v;   //解释下 在函数内部的变量都是局部变量,包括main 只在本地scope可见

class AA
{
private:
    int b;
    static int a ;
    // static int a = 0;  //编译不过   必须类外初始化
public:
    AA(/* args */){a++;};
    // static void BB(/* args */){b++;};   //编译不过   静态成员函数必须静态成员变量,初始化再全局区,局部this栈区都没有开辟 不会有局部变量
   
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


//作用域与生命周期 时空
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

int main()
{
    LOG( "this is cherno test...");
    test3();
    // std::cin.get();
}
int a = 111;   //全局区优先再编译时候处理,然后再找main 因此放在mian后面也能获取a的值