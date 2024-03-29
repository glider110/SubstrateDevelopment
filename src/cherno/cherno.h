/*
 * @Author: glider
 * @Date: 2023-05-27 11:07:59
 * @LastEditTime: 2023-07-14 10:26:01
 * @FilePath: /SubstrateDevelopment/src/cherno/cherno.h
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */


#include <iostream>
#include <string>

#define LOG(x)   std::cout << x <<std::endl

// static  int s_v = 3;   //链接阶段 只作用于本编译单元
int s_v = 3;


//类(封装继承多态)
namespace NS_CHERNO
{
// class AkAPI   final   //final关键字在类后确保不被继承
class AkAPI   
{
    public:
        // virtual AkAPI(){LOG("这是AkAPI构造函数");}  //基函数不可能是虚函数
        // AkAPI(){};
        virtual void func1() const=0;    //纯虚函数 ,必须再子类实现(抽象类)
        virtual void func2(){LOG("这是AkAPI::func2函数");}  ;  //虚函数
        // ~AkAPI(){LOG("析构基类");};
        virtual ~AkAPI(){LOG("析构基类");};
 };



class Entity final: public AkAPI   
{
private:
    int m_x;
    int m_y;
    mutable int m_z;
    const char* m_name ="ssss";  
    int* ptr_a = new int(10);  //glider !:类里面开辟数组/堆区一定要注意
    std::string   m_id;
public:
    static int sm_v;
    // static int s_v = 0;  //编译不过   必须类外初始化  加constexpr inline可以编译

public:
    Entity(const Entity& obj) = delete;     //glider note:一个类创建开始就含有6个隐藏函数
    Entity(Entity&& obj) = default;
    Entity& operator= (const Entity& obj) = default;
    Entity& operator= (Entity&& obj) = default;

    Entity(/* args */){
        sm_v++;    //类外初始化
        LOG("这是Entity构造函数");
    };
    // static void Entity(/* args */){m_x++;};   //编译不过   静态成员函数必须静态成员变量,初始化再全局区,局部this栈区都没有开辟 不会有局部变量
    Entity( int& x,const std::string& id):m_x(x),m_id(id) 
    {
        x++;   //如果是const就不行   ==const修饰形参==，防止形参改变实参
    }
    
    void func1()  const  override
    {
        // m_y++;   //不能操作类成员
        m_z = 1;
        m_z++;
        LOG("这是Entity::func2函数");
    }

    void func2() final {LOG("这是Entity::func2函数");}

    ~Entity()
    {
        LOG("析构派生类");
    };
};

int Entity::sm_v = 1;
}



