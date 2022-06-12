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

using namespace std;

void guo(){
    printf("ddddd");
}

void test510()
{
    ::pair<int ,string> a(2,"ffff"); //tuple一样
    a = make_pair(1,"fddd");
    a= make_pair<int ,string>(1,"fddd");
    

    ::map<int ,string> b = {{1,"guo"}};  //under_map?
    // ::map<int ,string> b ({{1,"guo"}});  //under_map?
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
template<typename type>

int main(int argc, char **argv) {

    test510();
    return 0;
}
