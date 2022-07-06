/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-06-10 11:03:44
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-06-16 09:56:42
 * @FilePath: /SubstrateDevelopment/example/carto_test.cpp
 * @Description: 
 */

#include <iostream>
#include <map>
#include <memory>
#include <string.h>
#include <vector>
#include <map>
#include <tuple>
#include  <functional>
#include  <thread>
#include <unistd.h>
#include <set>
#include <deque>
#include <queue>
#include<algorithm>

using namespace std;

class carto_test
{
private:
    /* data */
    int a =1;
    // static int  b = 2;  //报错
    public:
    carto_test(/* args */);
    ~carto_test();
};

carto_test::carto_test(/* args */)
{
}

carto_test::~carto_test()
{
}

/**
 * @brief: Briefly describe the function of your function
 * @param {int} a
 * @param {string} b
 * @param {vector<int>} c
 * @result: 
 */
int guo(int a,string b,vector<int> c){
    printf("ddddd\n");
}

//关键字: 容器 初始化make_pair/tuple/shared/
void test510()
{
    ::pair<int ,string> a(2,"ffff"); //tuple一样
    a = make_pair(1,"fddd");
    a= make_pair<int ,string>(1,"fddd");
    

    ::map<int ,string> b = {{1,"guo"}};  //under_map?
    // ::map<int ,string> b ({{1,"guo"}});  //under_map?
    std::map<int,string>  m_map;
    m_map.emplace(22,"guo");
    m_map.find(22);
    b={a};
    int c = b.begin()->first;

    std::set<int> m_set ={1,2,4,5};   //?
    
    vector<int> m_vec = {1,23,4};

    std::queue<int> m_queue({1,23,4});
    // std::queue<int> m_queue = {1,23,4};
    // std::deque<int> m_queue ={1,23,4};

    std::shared_ptr<int> a_ptr;
    a_ptr = make_shared<int>(10);


    std::thread handle;
    handle =std::thread([](){printf("hello world!");});
    // handle = std::thread(guo);
    handle.join();
    // handle.detach();
}

/**
 * @description: 
 * @return {*}
 */
//可调用对象
void test613()
{
     //  1
    typedef void(*func_type)(void);    // 是函数指针的类型定义，作用是声明一个 void(*)() 类型的函数指针 Func。
    func_type func2 = guo;    //赋值
    func2();         //调用
    //  2
    void (*func)(void) = guo;
    (*func)();
    //  3
    std::function<void(void)> func1 =guo;
    func1();
}

//C++强制类型转换
//https://blog.csdn.net/yueguangmuyu/article/details/114652055
void test_cast(){
    // float *a1 = new(float)(10.3f); 
    // float *a2 = new float(110.3f); 
    // int* b = dynamic_cast<int*>(a1);
    
    char a = 'a';
    int b = static_cast<int>(a);//正确，将char型数据转换成int型数据
}

//模板类
// template<typename type>

namespace NS_CALLBACK
{
    //回调函数
    using glider = std::function<void(int, string)> ;
    void addtrajectorbuilder(glider  pf, int a, string b){
    // glider glider_callback(1,"fan");
    pf(a,b);
}

} // namespace NS_CALLBACK

//回调函数实用小技巧
void test615(){
    std::vector<int> a{1,2,3,4,5,6};
    for_each(a.begin(),a.end(),[=](int value){cout <<value<<endl;});
    while (1)   //删除所有偶数的元素
    {
        auto it = find_if(a.begin(),a.end(),[=](int value){ return value%2 == 0;});
        std::cout << "result:" << *it << endl;
        if(it == a.end()) break;
        else a.erase(it);
    }
}

void test706(){
    int a;
    auto *b;
    

}


int main(int argc, char **argv) {
    // NS_CALLBACK::glider glider1(0,"guo");
    // int result_int;
    // string result_str;
    NS_CALLBACK::addtrajectorbuilder([](int p_a ,string p_b){ 
        int aa = p_a +10;
        std::cout << aa << endl;
    }, 3 ,"xiaofan");
    // test615();
    // carto_test cart;
    return 0;
}
