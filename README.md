# SubstrateDevelopment

**Project substrate development and practical verification of basic functions**

> <font color=green>**在此框架下以练带学,实际动手验证算法，不惧动手；**</font>
>
> **<font color=green>开发出现的编译错误能快速定位分析，而不是烦躁和逃避；</font>**
>
> <font color=green>**持续更新>>.....**</font>     

---

### **TODO LIST:**

#### 1.项目基础:

- [X] **编译及调试相关(CMAKE)**
  - [X] g++编译一个main的可执行文件、库文件，单文件，多文件   源头分目录；
  - [X] cmake编译：单文件 多文件  多目录形式   编译为动态库 可执行文件；
  - [X] cmake编译：调用库编译可执行文件，调用第三方库编译可执行文件；
  - [X] 分CMakeLists编译，脚本一键执行
  - [X] 调试：gdb调试和可视化调试，配置好制动化编译 调试 运行脚本
  - [X] 宏定义预编译选项按钮;
  - [X] 配置coredump文件应对偶发段错误;
  - [ ] cmake专题:find_package理解,制作标准化库模块;
  - [X] 添加glog作为日常调试;
  - [X] 标准化一个cmakelist项目(嵌套/平台/模式/编译脚本/cmake控制/安装/cmake_module)
  - [ ] 利用chatgpt来写cmake脚本
  - [ ] 完整项目文件管理
  
    * [X] [ 配置文件(lua yaml json)  选择轻量化的json](utils/json11.hpp)
    * [X] 日志文件(glog dblog)
    * [X] 调试文件(csv bmp )
    * [X] 保存控制台数据再以脚本分析 >>log.txt
- [ ] **C++语法相关**

  - [X] 宏定义的理解和常用方法；
  - [ ] 常用数据类型的应用：eigen opencv pcl  map vecter list
  - [X] 关于指针：三维矩阵 智能指针 普通指针
  - [X] lamda表达式的练习;
  - [X] 智能指针理解和练习;
  - [X] 结构体初始化列表;
  - [ ] 线程池;
  - [X] 多线程加锁;
  - [X] protobuffer运行demo;
  - [X] template;
  - [X] 集成一个超级类,覆盖工作中的基本知识点;
  - [X] 添加单例模式



#### 2.PCL点云学习

- [X] 自备的点云处理工具库...持续更新
- [X] 平面投影的凹凸包边界提取;
- [X] 贪婪三角面片重建,理解pcl::PolygonMesh数据结构;



#### 3.SLAM学习

- [ ] eigen_test.cpp测试(旋转的四种格式转换 /变换矩阵);
- [ ] 【深蓝学院】激光SLAM理论与实践



#### 4.ROS学习

- [X] **ros系统练习**

  - [X] 基本概念(packg,node,topic,message.lauch);
  - [X] 构建一个基本的catkin包流程;
  - [ ] 把李想的0到1搭建slam系统全部基于ros实际操作一遍就够了;



#### 5.效率工具

- [x] docker容器,隔绝本地环境,独立办公,跨平台移植;
- [x] 自动化脚本,常用模块pyautogui,pynput,selenium

------
------
------


| **<font color=red>专业基础</font>** | **[C++基础  黑马程序员](https://github.com/Blitzer207/C-Resource)**         **[Python 黑马程序员](https://github.com/hyh1750522171/bigData/tree/master/He%20Yihao)**        **[设计模式](https://github.com/FengJungle/DesignPattern)**   [大丙爱编程](https://subingwen.cn/)   [cherno](https://www.bilibili.com/video/BV1eu411f736/?spm_id_from=333.999.0.0&vd_source=7f98e46af73470a39ad6b1a64611b176) |
| ----------------------------------- | ------------------------------------------------------------ |
| **<font color=red>slam</font>**     | [**从零开始搭二维激光SLAM --- 基于ICP的帧间匹配**](https://blog.csdn.net/tiancailx/article/details/110822624)     **李想_cartograph付费课程** |
| **<font color=red>点云处理</font>** | [**CSDN:PCL学习付费专栏**](https://blog.csdn.net/qq_36686437/category_9913573.html)      **宏威8K点云处理课程**     [**双愚自动驾驶博主**](https://www.yuque.com/huangzhongqing/pcl/ape8sl) |
| **<font color=red>ROS</font>**      | **[大学生mooc  机器人操作系统入门](https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/chapter1/1.3.html)** |

#### **优质资料汇总:**

- **Linux系统编程网址：**               							https://www.bilibili.com/video/BV1KE411q7e 
- **Linux网络编程网址：**               			                https://www.bilibili.com/video/BV1iJ411S7UA
- **C++基础第一部分：**   		 		                      	https://www.bilibili.com/video/BV1RW41147iK
- **C++基础第二部分：**  	 	 			                      https://www.bilibili.com/video/BV1RW411476t
- **stl教程网址：**         		  				                     https://www.bilibili.com/video/BV1PW411t7Xg
- **设计模式教程网址：**           			                  	https://www.bilibili.com/video/BV1KW411t7FV  
- **Cherno C++【英文】**	         		                  	https://www.bilibili.com/video/BV1fP4y1w7iE/
- **中科院软件所-机器人操作系统入门** 		           https://www.bilibili.com/video/BV1mJ411R7Ni/?vd_source=7f98e46af73470a39ad6b1a64611b176
- **B站up面试汇总**                                                     https://github.com/lxiao217/study428/
- **张虎《机器人SLAM导航核心技术与实战》**        https://github.com/xiihoo/Books_Robot_SLAM_Navigation



