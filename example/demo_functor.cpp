/*
 * @Author: glider
 * @Date: 2023-07-12 22:20:28
 * @LastEditTime: 2023-07-12 22:20:42
 * @FilePath: /SubstrateDevelopment/example/demo_functor.cpp
 * @Version:  v0.01
 * @Description: 仿函数，并不是函数，却有着类似于函数的行为，简单地说就是重载括号运算符号。
                                    把对象当作一个函数用,仿函数拥有自己的数据成员，意味着仿函数拥有状态；
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include<iostream>
#include<algorithm>
using namespace std;

struct ADD {
	int num;
	ADD(int a){  //构造函数
		num = a;
	}
	int operator()(int x) {  //重载括号运算符
		return x + num;
	}
};

struct small {
	bool operator()(int a, int b) {
		return a < b; //如果第一个数小于第二个数返回true，排序是从小到大排列。返回真第一个参数的优先级高。
	}
};

class myclass
{
public:
	myclass(int x) : x_(x) {};
	int operator()(const int n) const { //这里加上const比较好，保护const int n，n不会被改变
		return n * x_;
	}
private :
	int x_;
};

int main(int argc, char** argv)
{
	// 1 struct结构体仿函数
	ADD add1(1);
	ADD add23(23);
	cout<<add23(55) << endl; //78
	cout<<add1(55) << endl;  //56
	cout << "-----------" << endl;
	// 2 匿名对象排序
	cout<<ADD(11).num << endl;  //ADD(11)相当于是匿名对象，也可以携程 a = ADD(11),a.num
	//匿名对象：不定义直接调用
	int a[] = { -4, -8, 2, -9,0 };
	int len = sizeof(a) / sizeof(a[0]);
	//sort(a, a + len, small());  //这里small()也是匿名对象（括号不要忘了）, 这句需要加上include<algorithm>
	sort(a, a + len, less<int>());  //stl自带，从小到大
	sort(a, a + len, greater<int>());  //stl自带，从大到小
	for(int i=0;i<=len-1;i++){ 
		cout << a[i] << endl;  //a
	}
	cout << "-----------" << endl;
	// 3 class类仿函数
	myclass C(2);
	cout << C(10) << endl;

	return 0;
}
