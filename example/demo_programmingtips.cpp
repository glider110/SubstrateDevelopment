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
#include <string>
using namespace std;

//标准类格式 类的成员变量的写法   函数赋值   this
namespace NS_CLASS_STYLE {
    class demo_programmingtips {

     public:
        int m_a;

        void init();                          //初始化输入     一些动词:add set get input updata 
        void set();                          //设置参数
        void output();                  //类输出
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
// auto test1 = [&](int argc, char **argv) {
//     cout << "argc: " << argc << endl;
//     for (int i = 0; i <= argc; ++i) {
//         cout << i << "  ";
//         cout << argv[i] << "   " << endl;
//     }
// };

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
    std::shared_ptr<int> ptra6 =nullptr;
    std::shared_ptr<int> ptra7 = std::make_shared<int>();
    // std::shared_ptr<int> ptra8 =  ptra8.reset(new int(*a));
    // std::shared_ptr<int> ptra9 = nullptr;
    std::shared_ptr<int> ptra9;
    ptra9.reset(new int(*ptra));
    // ptra9.reset(ptra);    //写法报错
    // std::shared_ptr<int> ptra9.reset(new int(*ptra));//这样直接reset不行
    
    // std::shared_ptr<int> ptra3 = new int(a);    //这种写法不对   对象和指针的区别
    std::cout << ptra.use_count() << " "<< ptra<<std::endl;
    std::cout << ptra2.use_count() << " "<< ptra2<<std::endl;
    std::cout << ptra3.use_count() << " "<< ptra3<<std::endl;
    std::cout << ptra4.use_count() << " "<< ptra4<<std::endl;
    std::cout << ptra5.use_count() << " "<< ptra5<<std::endl;
    std::cout << ptra6.use_count() << " "<< ptra6<<std::endl;
    std::cout << ptra7.use_count() << " "<< ptra7<<std::endl;
    // std::cout << ptra8.use_count() << " "<< ptra8<<std::endl;
    std::cout << ptra9.use_count() << " "<< ptra9<<std::endl;
   std::shared_ptr<int> aa = std::make_shared<int>();
//    std::shared_ptr<int> aa ;
     *aa= *ptra;
      std::cout  << " aa "<< *aa << "   "<<aa <<std::endl;
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
    int bb1[3]{1,2,3};
    // int cc[3] (1, 3,4);
    string aaa = "fsdfsdf";
    string aaa1("xxxxx");
    string aaa2{"fsdfs"};
    // strcpy();

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

//c++11 关键字
void test5()
{
//关键字:typedef typename decltype 
//               break continue return
//               override   final
typedef  vector<int ,string>  glider;
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

//容器1: array enum struct
void test7()
{
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

    //结构体的形式真是太灵活了!
    struct student
    {
        int m_age;
        string m_name;
        student(int, string ):m_age(99),m_name("glider"){};
        // student(int age, string name ):m_age(age),m_name(name){};
        student():m_age(10),m_name("guo"){};

    }guo2{12 , "fan"}, guo4;

    student guo1(week::CC , "xiao");
    student guo3;
    cout << guo4.m_age<<endl;
    cout << guo3.m_age<<endl;
    cout << guo2.m_age<<endl;
    cout << guo1.m_age<<endl;
    cout << demo_programmingtips.id<<endl;

    //数组
    int * array = new int[3]{1,2,3};
    cout <<"数组:" <<array[0]<<endl;

}

/**容器2:
 **数组:vector  deque
 **堆栈:queue stack
 **链表:list
 **关系性容器:tuple tie map set 
 **/
void test8()
{
    pair<string, int> a1("aa", 10);
    pair<string, int> a2{"aa", 10};
    cout << a2.first <<endl;
}


/**右值引用 
 ** move   右值有那些?字面量 将死值 move转移的值
 **理解右值引用在　深拷贝/浅拷贝过程的运用
 **数据类型只有　变量类型　指针　引用类型
 **/
int  print_(){printf("hello glider1...\n");return 1;}
void test9()
{
auto test91 = []()
{
    cout << R"(xxxxx)"<<endl;
    int aa = 1;
    return  aa;
};
    int a = 3;
    // int && b = a;//error
    // int & b = 3;   //引用必须要有地址；否则加const
    int && c = move(a);    //move转移　左值→右值
    int && d = forward<int>(a);
    int && d1(forward<int>(a));   //完美转发forward
    const int& b = test91();
    int b3 = print_();
    // int& b2 = print_();
    int&&  b1 = test91();
}

/**初始化方式思考
 ** 方式：构造　赋值　初始化列表
 **委托　继续　拷贝
 **（）　＝　｛｝:m_a(a)
 **/
int test10()
{

}


/**C++数据种类特性思考
 ** 时空：生命周期　作用域　读写
 ** 这就是ｃ语言比其他语言难很多的原因
 **/
// void fun3(){
//     b++;
// }  //关于作用域 针对函数嵌套函数 并不是上一层数据能被下一层读写 之前一直模糊不清 基础太差了
int test_static(){
    static int b = 1;
    // static int a = 1;
    static int c =2;
    // {static int c = 1;
    // std::cout << c <<  std::endl;}
    // std::cout << c <<  std::endl;

    for(int i = 0; i <10 ;i ++){
        static int b = 2;
        // {b++;}
        // fun3;
        std::cout << b <<  std::endl;
    }
}



//结构化绑定
// std::tuple<std::string, int> CreatePerson()
// {
//     return { "小岛秀夫赛高", 56 };
// } 
int test11()
{
    auto CreatePerson =[&]()->std::tuple<std::string, int> 
    {
        // return { "小岛秀夫赛高", 56 };
        int x = 1; 
        string y = "aaa"; 
        return {y, x};
    } ;
    string xx, xx1;
    int yy, yy1;
    // auto [xx, yy] = CreatePerson();// C17标准
    tie(xx, yy) =  CreatePerson();
    std::tuple<std::string, int> guo1{"xiaofan", 29};
    std::pair<std::string, int>  guo2{"xiaofan111", 111};
    using data_bind1 = std::tuple<std::string, int>;
    typedef std::tuple<std::string, int> data_bind2; 
    data_bind2 guo3("xiaofan222", 222);
    data_bind2 guo4 = make_tuple("xiaofan333", 333);
    string name = std::get<0>(guo1);
    tie(xx, yy) =  guo1;
    tie(xx1, yy1) =  guo2;
    cout<< "测试数据绑定:" << guo2.first << "" << xx1<<endl;
    cout<< "测试数据绑定:" << xx <<endl;
}


//包装器和绑定器
void print1(){printf("hello glider1...\n");}
void print2(string a, string b){
    cout << "hello glider2..." << a << b << endl;
}
void output(int x, int y)
{
    cout << x << " " << y << endl;
}
void test12(void)
{
    std::function<void(void)> f1 = print1;
    // auto f1 = print1;
    auto f2 = std::bind(print2,"xiao", "fan");
    std::bind(print2, placeholders::_1, "fan")("da");
    f1();
    f2();
    bind(output, 1, 2)();
}

/*const
**修饰常量 
**修饰函数参数 修饰函数返回值 修饰函数
**修饰成员函数    成员变量不能被修改 即修饰this指针
*/
int& func(); //函数声明
const int& func1(); //函数声明
const int func2(); //函数声明
// void test13(void)  const  自能修饰成员函数
// void test13(void)  
// {
//     int b = func();                                    
//     int b1 = func1();                                    
//     int b2 = func2();                                    

//     int& c = func();                          
//     // int& c1 = func1();                          
//     int& c2 = const_cast<int&>(func1());         
//     const int& c3 = func();                        //正确
//     // int& c4 = func2();                          
// }


//指针 线程 绑定器 lamda表达式 嵌套使用   这个的核心.这个弄明白了很多都理解了!!!!
//小技巧:再ak_sdk里面搜bind会有很多案例学习,这种学习方式比较好
// std::thread(std::bind(&ImuCtrl::RunRecvThread, this)).detach();
//
void test14(void)
{
    auto print = [](){printf("hello world!");};
    // print();
    function<void(void)> print1_fuction(print);
    print1_fuction();
    auto print_bind = bind(print);
    bind(print)();
    std::shared_ptr<thread> a_ptr(make_shared<thread>(print));
    a_ptr->detach();
    // this_thread::sleep_for(chrono::seconds(2));
    sleep(0.001);
    
    // std::unique_ptr(make_unique<std::thread>(print))->detach();
    std::shared_ptr<std::thread>(make_shared<std::thread>(print))->detach();
    vector<int>({1});

}

//测试string的方法
void test15(){
    string name ="/akb/map/123456.pbstream";
    string suffix = ".pbstream";
    string  name_no_suffix;
    int index = name.rfind("/");
    std::cout << "最后的/的索引位置: " <<index << endl;
    name_no_suffix = name.substr(0 ,name.size()- suffix.size());
    std::cout << "name_no_suffix: " <<name_no_suffix<< endl;
    std::cout << "name_id : " <<stoull(name_no_suffix.substr(index+1, name_no_suffix.size()))<< endl;
    std::string k = name_no_suffix.substr(index+1, name_no_suffix.size());
    uint64_t test = (uint64_t)reinterpret_cast<std::string*>(&k);
    std::cout << "name_id : " <<test<< endl;
    char name1[50];
    std::cin.getline(name1,50);
    std::cout << "name_id : " <<atoll(name1)<< endl;
}


struct OriginCollideSize {  // 避障尺寸,考虑到有可能会顶升货架,所以该尺寸是避障处理器的输入参数
    // 这个是货架的尺寸
    double width;
    double length;
};
typedef std::shared_ptr<OriginCollideSize> OriginCollideSize_Ptr;
OriginCollideSize aa{11,22};
OriginCollideSize_Ptr bb = make_shared<OriginCollideSize>(aa);



// 测试传参引用和指针
void test15_1(OriginCollideSize_Ptr a ){
    a->length = 111;
}
void test15_2(const OriginCollideSize_Ptr a ){
    a->length = 222;
}
void test15_3(const OriginCollideSize_Ptr &a ){
    a->length = 333;
}


int main(int argc, char **argv) {

    // test3();
    // test_static();
    // test1(argc, argv);
    // NS_CLASS_STYLE::demo_programmingtips aa(3);
    // aa.set();
    std::cout<<  bb->length<< std::endl;
    // test15_1(bb);
    // test15_2(bb);
    test15_3(bb);
    std::cout<<  bb->length<< std::endl;

    return 0;
}
