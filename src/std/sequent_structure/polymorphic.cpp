/*
 * @Author: glider gaoxiaofan@standard-robots.com
 * @Date: 2023-10-16 11:26:40
 * @LastEditors: glider gaoxiaofan@standard-robots.com
 * @LastEditTime: 2023-10-16 22:00:01
 * @FilePath: /SubstrateDevelopment/src/std/sequent_structure/no_para_structure.cpp
 * @Description:多态问题

*/

#include <iostream>
#include <string>
using namespace std;
class Parent 
{
public:
    /*我们写了构造函数,默认的构造函数就不存在了,子类构造函数报错
    Parent(string FName,string SName):FName(FName),SName(SName){}*/
	Parent() { cout << "父类无参构造函数sss" << endl; }
    void process(int a){cout << "父类函数 process" << endl;};
    // virtual void fun(int a) = 0;       //glider !:   //父类声明纯虚函数 子类必须要有实现  否则父类子类、实例化都不行
    virtual void eat(int a){cout << "父类虚函数 eat" << endl;};       //glider !:   //父类声明虚函数 子类父类各调各的

public:
	string FName = "guo";    //姓
	string SName = "fan";    //名
    
};
 
//单继承
class Son1 :public Parent
{
public:
/*对于子类,必须采用初始化参数列表的方式,如果想构造无参对象,且不想采用初始化参数列表
  的方式,父类中必须存在无参的构造函数,当然缺省也可以*/
	Son1() :Parent(){ cout << "子类无参构造函数" << endl; } 
    // void process(int a){cout << "子类函数 process" << endl;} ;   
    void fun(int a){cout << "子类函数 fun" << endl;}
    void eat(){cout << "子类虚函数 eat" << endl;};
protected:
	string sonFName;
	string sonSName;
  /*string FName;  子类继承父类属性的权限
	string SName;*/
};
 
int main() 
{
//子类构造对象,优先调用父类构造函数,再调用自己的构造函数
 
	Son1 son1;
    son1.eat();
    // son1.process(1);
    // cout << son1.SName << endl; 		
    // cout << son1.fun() << endl; 		
	// return 0;
    // cout << "================测试多态==================" <<endl;
    Parent parent;
    parent.eat(1);
    
    // parent.process(2);

}
/*输出*/
 
// 父类无参构造函数
// 子类无参构造函数