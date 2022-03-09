#include <iostream>
#include <map>
#include <memory>
#include <string.h>
#include <vector>
#include <map>

using namespace std;
namespace NS_CLASS_STYLE {
//标准类格式 类的成员变量的写法   函数赋值   this
class demo_programmingtips {

  public:
    int m_a;

    void init();                 //初始化输入
    void set();                  //设置参数
    void output();               //类输出
    demo_programmingtips(int a); //构造输入
    ~demo_programmingtips();

  private:
    int a_;
    string b_;
    int c_;
    int *d_;
};

void demo_programmingtips::set() {
    cout << "ssss" << c_ << endl;
    cout << "ssss" << b_ << endl;
}

demo_programmingtips::demo_programmingtips(int a) : a_(2), b_("dada") {
    this->c_ = a;
    this->d_ = nullptr;
}

demo_programmingtips::~demo_programmingtips() {}

} // namespace NS_CLASS_STYLE

//数据输入
auto test1 = [&](int argc, char **argv) {
    cout << "argc: " << argc << endl;
    for (int i = 0; i <= argc; ++i) {
        cout << i << "  ";
        cout << argv[i] << "   " << endl;
    }
};

// lamda表达式
void test2() {
    int a = 1;
    int b = 2;
    int c = 3;
    cout << "argc-out: " << a << endl;
    auto lamda = [=]() {
        cout << "argc: " << a << endl;
        cout << "argc: " << b << endl;
        //  a=22;
    };
    cout << "argc: " << a << endl;
    lamda();
    cout << "argc: " << a << endl;
}

//循环读取容器变量

//宏定义 变量和函数

//智能指针 vs 普通指针 指针数组
void test3() {
    // int a[] = {1, 2, 3};
    // int* b1 = new int(3);
    // int* b2 = new int[4];        //delete[] b2
    // int** bb=new int*[3];    //delete[][] bb        由于c++ 版本没有升级到11标准，不支持语法：int[][] states = new int[n][w];
    // std::shared_ptr<int> ptr1;
    // ptr1=std::shared_ptr<int>(new(int));   
    // std::shared_ptr<int> ptra = std::make_shared<int>(a);   //类的指针初始化一定要注意
    // *ptr1=1;
    int a = 10;
    std::shared_ptr<int> ptra = std::make_shared<int>(a);
    std::shared_ptr<int> ptra2(ptra); //copy
    std::shared_ptr<int> ptra3(new int(a));
    std::shared_ptr<int> ptra4;
    ptra4 = ptra3;
    std::shared_ptr<int> ptra5 = std::make_shared<int>(1);
    std::shared_ptr<int> ptra6 = nullptr;
    std::shared_ptr<int> ptra7 = std::make_shared<int>();

    // std::shared_ptr<int> ptra3 = new int(a);    //这种写法不对   对象和指针的区别
    std::cout << ptra.use_count() << " "<< ptra<<std::endl;
    std::cout << ptra2.use_count() << " "<< ptra2<<std::endl;
    std::cout << ptra3.use_count() << " "<< ptra3<<std::endl;
    std::cout << ptra4.use_count() << " "<< ptra4<<std::endl;
    std::cout << ptra5.use_count() << " "<< ptra5<<std::endl;
    std::cout << ptra6.use_count() << " "<< ptra6<<std::endl;
    std::cout << ptra7.use_count() << " "<< ptra7<<std::endl;
    int aa = *ptra7;
      std::cout  << " xxxxx "<< *ptra5<<std::endl;
      std::cout  << " xxxxx "<< *ptra7<<std::endl;
    int b = 20;
    int *pb = &a;
    // std::shared_ptr<int> ptrb = pb;  //error
    std::shared_ptr<int> ptrb = std::make_shared<int>(b);
    std::cout << ptrb.use_count() << " "<< ptrb<<std::endl;
    ptra2 = ptrb; //assign
    pb = ptrb.get(); //提供直接访问其原始指针的方法，用于向下兼容。
    std::cout << ptrb.use_count() << " "<< ptrb<<std::endl;
    std::cout << pb<<std::endl;
    // std::cout << ptra.use_count() << std::endl;
    // std::cout << ptrb.use_count() << std::endl;
}

//数组练习 数组赋值另外数组
void test4()
{
    std::cout  << "oooooooooooooooooooooooooooooooooooooo"<<std::endl;
    int aa[3] = {1, 3,4};
    // int bb[3];
    int* bb = new int[3];
    // bb = aa;
    memcpy(bb ,aa, 12);
    std::cout  << " xxxxx "<< aa <<std::endl;
    std::cout  << " xxxxx "<< bb <<std::endl;
    std::cout  << " xxxxx "<< &aa <<std::endl;
    std::cout  << " xxxxx "<< &aa[0] <<std::endl;
    std::cout  << " xxxxx "<< bb[0] <<std::endl;
    std::cout  << " xxxxx "<< bb[1] <<std::endl;
    std::cout  << " xxxxx "<< bb[2] <<std::endl;
    std::cout  << " xxxxx "<<sizeof(aa)/sizeof(int) <<std::endl;
}

//c++11 特性
void test5()
{
//关键字:typedef typename decltype 
//               break continue return
//               override   final
//容器: tuple tie map

    typedef  vector<int ,string>  glider;
    struct 
    {
        int id;
        string name;
    }demo_programmingtips;
    
    enum week
    {
        AA,
        BB,
        CC,
        // DD;     不是冒号
    };
    typedef struct student1
    {
        int AA;
        string name;
    };

}

/*预编译:
**1.头文件嵌入
**2.编译宏定义
**3.代码块控制
*/
 void  test6()
 {
//预处理关键字
    #ifndef    guo
    #define  guo
    #endif

    #ifdef  guo   //参考map头文件
    #endif

    #if  1
    #elif
    #else 
    #endif
// CMake option选项开关
    #ifdef TEST_DEBUG
    #endif

    #pragma once

 }

int main(int argc, char **argv) {

    // test1(argc, argv);

    test5();

    // NS_CLASS_STYLE::demo_programmingtips aa(3);
    // aa.set();

    return 0;
}
