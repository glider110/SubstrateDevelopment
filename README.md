# SubstrateDevelopment

**Project substrate development and practical verification of basic functions**

> <font color=green>**在此框架下以练带学,实际动手验证算法，不惧动手；**</font>
>
> **<font color=green>开发出现的编译错误能快速定位分析，而不是烦躁和逃避；</font>**
>
> <font color=green>**持续更新>>.....**</font>

------



### **TODO LIST:**

#### 1.项目基础:

- [x] **编译及调试相关(CMAKE)**

  - [x] g++编译一个main的可执行文件、库文件，单文件，多文件   源头分目录；

  - [x] cmake编译：单文件 多文件  多目录形式   编译为动态库 可执行文件；

  - [x] cmake编译：调用库编译可执行文件，调用第三方库编译可执行文件；

  - [x] 分CMakeLists编译，脚本一键执行

  - [x] 调试：gdb调试和可视化调试，配置好制动化编译 调试 运行脚本

  - [x] 宏定义预编译选项按钮;

  - [x] 配置coredump文件应对偶发段错误;

  - [ ] cmake专题:find_package理解,制作标准化库模块;

  - [x] 添加glog作为日常调试;

  - [x] 标准化一个cmakelist项目(嵌套/平台/模式/编译脚本/cmake控制/安装/cmake_module)

  - [ ] 利用chatgpt来写cmake脚本

  - [ ] 完整项目文件管理

    * [x] [ 配置文件(lua yaml json)  选择轻量化的json](utils/json11.hpp)
    * [x] 日志文件(glog dblog)
    * [x] 调试文件(csv bmp )
    * [x] 保存控制台数据再以脚本分析 >>log.txt

    

- [ ] **C++语法相关**
  - [x] 宏定义的理解和常用方法；
  - [ ] 常用数据类型的应用：eigen opencv pcl  map vecter list
  - [x] 关于指针：三维矩阵 智能指针 普通指针
  - [x] lamda表达式的练习;
  - [x] 智能指针理解和练习;
  - [x] 结构体初始化列表;
  - [ ] 线程池;
  - [x] 多线程加锁;
  - [x] protobuffer运行demo;
  - [x] template;
  - [x] 集成一个超级类,覆盖工作中的基本知识点;
  - [x] 添加单例模式



#### 2.PCL点云学习

- [x] 自备的点云处理工具库...持续更新





#### 3.SLAM学习

- [ ] eigen_test.cpp测试(旋转的四种格式转换 /变换矩阵);
- [ ] 【深蓝学院】激光SLAM理论与实践





#### 4.ROS学习

- [X] **ros系统练习**

  - [X] 基本概念(packg,node,topic,message.lauch);
  - [X] 构建一个基本的catkin包流程;
  - [ ] 把李想的0到1搭建slam系统全部基于ros实际操作一遍就够了;
