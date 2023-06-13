/*
 * @Author: glider
 * @Date: 2023-05-27 11:07:59
 * @LastEditTime: 2023-06-13 23:29:54
 * @FilePath: /SubstrateDevelopment/example/cherno.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */

#include <string>
// static  int s_v = 3;   //链接阶段 只作用于本编译单元
int s_v = 3;






class Entity
{
private:
    int m_x;
    int m_y;
    mutable int m_z;
    const char* m_name;  
    std::string   m_id;
    static int sm_v;
    // static int s_v = 0;  //编译不过   必须类外初始化

public:
    Entity(/* args */){sm_v++;  
    };
    // static void Entity(/* args */){m_x++;};   //编译不过   静态成员函数必须静态成员变量,初始化再全局区,局部this栈区都没有开辟 不会有局部变量
    Entity( int& x,const std::string& id):m_x(x),m_id(id) 
    {
        x++;   //如果是const就不行   ==const修饰形参==，防止形参改变实参
    }
    
    void func1() const
    {
        // m_y++;   //不能操作类成员
        m_z = 1;
        m_z++;
    }

    ~Entity();
};


