### 基版开发log：

1. 建立框架模型
2. g++编译一个main的可执行文件，单文件
3. g++编译一个main的可执行文件，多文件   源头分目录
4. g++编译一个main的可执行文件，多文件   源头同目录
5. cmake编译：单文件 多文件  动态库 可执行文件  main函数调用运行；



### 待验证任务：

- [ ] 宏定义的理解和常用方法



### 开发疑问：

* ==定义 实现== -==声明 引用==   的深度理解？

* g++的用法和gcc类似，编译C++的时候比gcc更简单，因为它会自动链接到C++标准库，而不像gcc需要手工指定。
  g++ main.cpp -o main
  g++ testspeaker.cpp speaker.cpp -o testspeaker
  
* 关于头文件

  - **[#include 是什么意思？](https://zhidao.baidu.com/question/151006287.html)**直白的说，它就是告诉你，在这个地方，你要插入一堆代码，这堆代码在另一个文件里。

  * .h 让各个分开的文件结合起来编辑  可以声明多次 但不能定义多次  （错误认识）
  * 头文件<>    ""[**区别**]()
  * 通俗的说：在C系统的编程语言中，#include是为了声明在这个地方插入别的文件中的代码。



### 报错汇总：(特别熟练的看明白报错信息)

1. 定义了没实现

   ```shell
   ：/tmp/ccIji8Yp.o：在函数‘main’中：
   main.cpp:(.text+0x48)：对‘person::person()’未定义的引用
   main.cpp:(.text+0x54)：对‘person::say()’未定义的引用
   main.cpp:(.text+0x60)：对‘person::~person()’未定义的引用
   main.cpp:(.text+0x85)：对‘person::~person()’未定义的引用
   collect2: error: ld returned 1 exit status
   ```

   

2. 重复定义/重复实现

   ```shell
   ./src/person.cpp:4:7: error: redefinition of ‘class person’
    class person
          ^~~~~~
   In file included from ./src/person.cpp:2:0,
                    from main.cpp:4:
   ./src/../include/person.h:2:7: note: previous definition of ‘class person’
    class person
          ^~~~~~  
   ```

   **[\#pragma once](https://www.cnblogs.com/qiang-upc/p/11407364.html)**  能解决部分问题（只能处理同一个文件的定义被多次include的问题）

3. 重复声明

   ```shell
   main.cpp: In function ‘int main()’:
   main.cpp:15:9: error: redeclaration of ‘person glider’
     person glider;
            ^~~~~~
   main.cpp:14:9: note: ‘person glider’ previously declared here
     person glider;
   ```

   



