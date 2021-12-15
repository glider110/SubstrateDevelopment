#include <iostream>
#include <map>
#include <memory>

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
    int a[] = {1, 2, 3};
    int* b1 = new int(3);
    int* b2 = new int[4];        //delete[] b2
    int** bb=new int*[3];    //delete[][] bb        由于c++ 版本没有升级到11标准，不支持语法：int[][] states = new int[n][w];
    std::shared_ptr<int> ptr1;
    ptr1=std::shared_ptr<int>(new(int));   
    std::shared_ptr<int> ptra = std::make_shared<int>(a);   //类的指针初始化一定要注意
    *ptr1=1;

}

int main(int argc, char **argv) {

    // test1(argc, argv);

    test2();

    NS_CLASS_STYLE::demo_programmingtips aa(3);
    aa.set();

    return 0;
}
