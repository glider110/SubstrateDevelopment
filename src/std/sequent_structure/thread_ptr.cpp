#include <iostream>
#include <thread>
#include <memory>
#include <string>
#include <functional>
#include <time.h>
#include <unistd.h>

using namespace std;

#define    LOG(x)  cout<<x<<endl

struct Para
{
    shared_ptr<int >   id;
    string name = "xxx";
     
};

void func_set(Para para){

    while (true)
    {
    usleep(500*1000);
    LOG(para.name);
        
    }
    

}

void func_get(){

}



int main(void){
    
    Para para;
    // LOG(para.name);
    

    // shared_ptr<thread>(new thread(func_set))->detach();
    shared_ptr<thread>(make_shared<thread>(func_set, para))->detach();

    while (1)
    {
        sleep(1);
    }
    
    

}