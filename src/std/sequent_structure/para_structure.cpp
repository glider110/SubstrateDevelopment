#include <string>
#include <iostream>
using namespace std;

class Parent
{
public:
 
//需要写两个参数的构造函数
	Parent(string FName, string SName) :FName(FName), SName(SName)
	{
		cout << "父类有参构造函数" << endl;
	}

    Parent() 
	{
		cout << "父类wuwuwuwuwu参构造函数" << endl;
	}
protected:
	string FName;    //父姓
	string SName;    //父名
};
 
//单继承
class Son :public Parent
{
public:
/*传参随意,不传变量FName|直接传常量初始化FName也可以|参数从哪里传进来无所谓
  只要类型|个数和父类构造函数一致就行了,可以不使用,但是必须要传
    Son(string FName, string SName, string sonSName) :Parent("k", SName)
    { 
    }
*/
	// Son(string FName, string SName, string sonSName) :Parent(FName, SName)
	Son(string FName, string SName, string sonSName) 
	{
		//自己的属性用什么方式初始化都行    this指针|初始化参数列表
		this->sonFName = FName;     //子姓和父亲姓相同,继承父亲姓即可
		this->sonSName = sonSName;  //自己的名
		cout << "子类有参构造函数" << endl;
	}
	void print()        //父类属性不是private属性,可以直接访问
	{
		cout << "父:" << FName + SName << endl;
		cout << "子:" << sonFName + sonSName << endl;
	}
protected:
	string sonFName;    //子姓
	string sonSName;    //子名
  /*string FName;       父类中属性在子类中的权限是保护类型
	string SName;       必须调用父类的构造函数初始化*/
};
 
int main()
{
	Son son("小","白","黑");  //子类构造对象,优先调用父类构造函数,再调用自己的构造函数
	son.print();
	return 0;
}
/*输出*/
 
// 父类有参构造函数
// 子类有参构造函数
// 父:小白
// 子:小黑