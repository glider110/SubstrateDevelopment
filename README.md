# SubstrateDevelopment

**Project substrate development and practical verification of basic functions**

> **解决一个项目的基本构建方式，理清结构；**
>
> **搭建编程环境，实际动手验证算法，不惧动手；**
>
> **开发出现的编译错误能快速定位分析，而不是烦躁和逃避；**

**TODO LIST:**

- [X] 建立框架模型；
- [X] **编译相关**

  - [X] g++编译一个main的可执行文件、库文件，单文件，多文件   源头分目录；
  - [X] cmake编译：单文件 多文件  多目录形式   编译为动态库 可执行文件；
  - [X] cmake编译：调用库编译可执行文件，调用第三方库编译可执行文件；
  - [X] 分CMakeLists编译，脚本一键执行
- [X] 宏定义的理解和常用方法；
- [X] 自备的点云处理工具库...持续更新
- [X] 调试：gdb调试和可视化调试，配置好制动化编译 调试 运行脚本
- [ ] 常用数据类型的应用：eigen opencv pcl  map vecter list
- [X] 关于指针：三维矩阵 智能指针 普通指针
- [ ] *个人工具库收*

  - [ ] 数据流读写：txt、csv、bmp、ply  log写法标准;
  - [X] 时间接口
- [X] lamda表达式的练习;
- [X] 智能指针理解和练习;
- [X] 宏定义预编译选项按钮;
- [X] 结构体初始化列表;
- [ ] 线程池;
- [X] 配置coredump文件应对偶发段错误;
- [X] 多线程加锁;
- [ ] cmake专题:find_package理解,制作标准化库模块;
- [ ] eigen_test.cpp测试(旋转的四种格式转换 /变换矩阵);
- [X] protobuffer运行demo;
- [X] **ros系统练习**

  - [X] 基本概念(packg,node,topic,message.lauch);
  - [X] 构建一个基本的catkin包流程;
  - [ ] 把李想的0到1搭建slam系统全部基于ros实际操作一遍就够了;
- [X] template;

* [ ] github获取文件管理系统, 日志管理系统,程序检测系统;
* [ ] 添加glog作为日常调试;
* [ ] 完整项目文件管理
  * [X] [ 配置文件(lua yaml json)  选择轻量化的json](utils/json11.hpp)
  * [ ] 日志文件(glog dblog)
  * [ ] 调试文件(csv bmp )
  * [ ] 保存控制台数据再以脚本分析 >>log.txt

- [X] 集成一个超级类,覆盖工作中的基本知识点;
  - [ ] 添加单例模式
- [ ] 标准化一个cmakelist项目(嵌套/平台/模式/编译脚本/cmake控制/安装/cmake_module)
- [ ] 利用chatgpt来写cmake脚本
