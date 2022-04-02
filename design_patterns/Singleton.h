/**实现单例step
 * 1.构造函数私有化
 * 2.添加静态私有化指针
 * 3.提供外部静态接口
 * 参考:https://blog.csdn.net/weixin_42636062/article/details/119938514
 **/

#include <iostream>
#include <stdlib.h>

class Singleton
{
public:
    static Singleton* getinstance()
    {
        if(m_instance == NULL)
        {
            m_instance =  new(Singleton);
        }
         return m_instance;
    };
private:
    Singleton(/* args */);
    ~Singleton();

private:
    static Singleton* m_instance;
};

//恶汉式　再mian启动之前就初始化静态变量的值了
// Singleton* Singleton::m_instance = new(Singleton);
// Singleton* Singleton::m_instance = new Singleton;

//懒汉式 在创建时才给地址赋值(初始化下层到类里面)
Singleton* Singleton::m_instance = NULL;

Singleton::Singleton(/* args */)
{
    std::cout << "无参构造..." << std::endl;
}

Singleton::~Singleton()
{
    std::cout << "析构..." << std::endl;
    delete m_instance;

}
