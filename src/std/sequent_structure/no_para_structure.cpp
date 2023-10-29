/*
 * @Author: glider gaoxiaofan@standard-robots.com
 * @Date: 2023-10-16 11:26:40
 * @LastEditors: glider gaoxiaofan@standard-robots.com
 * @LastEditTime: 2023-10-16 21:16:50
 * @FilePath: /SubstrateDevelopment/src/std/sequent_structure/no_para_structure.cpp
 * @Description:继承问题
 * 子类想构造无参对象，父类必须要写无参构造函数(隐式调用构造函数)
				https://blog.csdn.net/weixin_60569662/article/details/121677816
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
protected:
	string FName;    //姓
	string SName;    //名
};
 
//单继承
class Son :public Parent
{
public:
/*对于子类,必须采用初始化参数列表的方式,如果想构造无参对象,且不想采用初始化参数列表
  的方式,父类中必须存在无参的构造函数,当然缺省也可以*/
	Son() :Parent(){ cout << "子类无参构造函数" << endl; }    
protected:
	string sonFName;
	string sonSName;
  /*string FName;  子类继承父类属性的权限
	string SName;*/
};
 
int main() 
{
//子类构造对象,优先调用父类构造函数,再调用自己的构造函数
 
	Son son;		//初始化参数列表的隐式写法
	return 0;
}
/*输出*/
 
// 父类无参构造函数
// 子类无参构造函数