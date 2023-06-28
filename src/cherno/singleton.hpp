/*
 * @Author: glider
 * @Date: 2023-06-28 15:06:31
 * @LastEditTime: 2023-06-28 19:51:27
 * @FilePath: /SubstrateDevelopment/src/cherno/singleton.hpp
 * @Version:  v0.01
 * @Description: 手写单例模式,分为懒汉模式和饿汉模式(初始化方式不一样)
 * glider url:https://blog.csdn.net/weixin_42636062/article/details/119938514
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
// glider note:1.懒汉式(需要的时候才会创建) 
// glider note:2.饿汉式(直接创建，理解为main执行前，就创建好了)
//method:    实现单例步骤
//method: 1.构造函数私有化
//method: 2.增加静态私有的当前类的指针变量
//method: 3.提供静态对外接口，可以让用户获得单例对象

#include<iostream>
#include <functional>
#include<stdio.h>

class singleton
{
public:
    static singleton* GetInstance()
    {
        return ptr_singleton;
    }
    void print_ff()
    {
        std::cout<< "这是个print_ff()" <<std::endl;
    }
    ~singleton();

private:
    singleton(/* args */){
     std::cout<< "这是个单例" <<std::endl;
    }
    static singleton* ptr_singleton;

};

//类外初始化ptr_singleton
singleton* singleton::ptr_singleton = new singleton();

// static singleton* singleton::GetInstance()
// {
//     // if (!ptr_singleton)
//     // {
//     //     ptr_singleton = new singleton();
//     // }
//     return ptr_singleton;
// }

// singleton::print_ff()
// {
//     std::cout<< "这是个print_ff()" <<std::endl;
// }

// singleton::singleton(/* args */)
// {
//      std::cout<< "这是个单例" <<std::endl;
// }

// singleton::~singleton()
// {
//     delete ptr_singleton;
// }
