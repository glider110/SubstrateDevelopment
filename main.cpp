// #include  <iostream>    //""  和 <>  diff
#include "iostream"
#include <stdio.h>
// #include "./src/person.cpp"  //ide可能检索不到路径 需要到.vscode设置
                                                            //添加这句后g++不需要多文件加入  加入反而多次定义  
                                                            //深刻理解.cpp .h 的本质 
# include "./include/person.h"          
#include "./cat/cat.h"                                             

int  main()
{
 std::cout<<"glider"<<std::endl;
 person glider;
 glider.say();
 cat sta;
 sta.say();


}