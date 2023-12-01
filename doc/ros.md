---
title: LINUX效率工具：
date: YYYY-MM-DD HH:MM:SS
tags: 开发记录
categories: ros
typora-root-url: ros
---



* [ ] catkin_create 和catkin_make 的区别;
* [ ] ros不容许有中文路径,只能换到主目录下    /home/glider/project/L12/code....

#### 常用命令:

`rostopic list -v    可以看全发布和订阅个数`

rosnode list   查看所有运行的节点

rospack list |grep lesson   查看lesson的包

rospack profile 查看  查看运行环境包含关注空间没有

rosrun lesson1 *node

学习思路:(把这四步弄明白,基本ROS入门))

1. 查看工作空间有多少个包 rospack profile
2. 查看包里面多少个节点       rospack list |grep *     rosrun lesson1 *node  (借助rosrun 包 两次tab补全)
3. 查看一个节点有多少话题/服务  rosnode info 节点  rostopic echo /laser_scan |grep frame*(查看id 有些时候rviz显示不出点云)
4. 查看话题/服务的数据类型    rosmsg info

#### 概念:

* [ ] ROS的workspace ,package, 节点的区别;
* [ ] 话题和消息类型得区别;话题和服务区别;





以下是将以上提问和回答输出为Markdown格式的示例：

---

## 提问：指定的源代码目录不存在

这个错误提示说明你指定的源代码目录`/home/glider/workspace/src`不存在。

要解决这个问题，你需要确保在ROS工作空间的根目录下存在一个名为`src`的目录。在你的情况下，检查`/home/glider/workspace`目录下是否存在`src`目录。

如果`src`目录不存在，你可以手动创建它。在终端中进入ROS工作空间的根目录，然后执行以下命令：

```bash
mkdir src
```

创建`src`目录后，再次运行`catkin_make`命令，它应该能够正确地找到源代码目录并进行编译。

---

## 提问：启动ROS

要启动ROS，你需要按照以下步骤进行操作：

1. 打开一个终端。
2. 在终端中输入以下命令来启动ROS的核心功能：

```bash
roscore
```

这将启动ROS的主节点，它负责协调ROS系统中的各个节点之间的通信。

3. 在另一个终端中，你可以运行ROS节点或执行其他与ROS相关的操作。例如，你可以运行一个ROS包中的节点，使用ROS提供的工具进行数据发布和订阅，或者使用ROS的命令行工具进行调试和监控。

请注意，如果你使用的是ROS的分发版（如ROS Kinetic、ROS Melodic等），你可能需要在终端中先执行以下命令来设置ROS环境变量：

```bash
source /opt/ros/<ROS版本>/setup.bash
```

确保将`<ROS版本>`替换为你正在使用的ROS版本，例如`melodic`或`noetic`。

通过以上步骤，你应该能够成功启动ROS并开始使用它的功能。

---

## 提问：Devel space

在ROS中，"devel space"是指ROS工作空间中的一个目录，用于存放编译后生成的可执行文件、库文件和其他构建产物。

通常，"devel space"目录位于ROS工作空间的根目录下的`devel`目录中。在这个目录中，你可以找到编译后生成的可执行文件和库文件，以及其他与ROS包构建相关的文件。

在使用`catkin_make`或其他构建工具编译ROS包时，编译产物将被放置在"devel space"目录中。这些文件可以通过设置正确的环境变量来让ROS系统能够找到并使用它们。

需要注意的是，"devel space"目录中的文件是根据ROS包的CMakeLists.txt文件和package.xml文件进行编译生成的，因此在编译之前，确保这些文件的配置正确无误。

总结起来，"devel space"是ROS工作空间中用于存放编译产物的目录，它包含了编译后生成的可执行文件、库文件和其他构建相关的文件。

---

## 提问：Error: Configuring incomplete, errors occurred!

这个错误提示表明在配置ROS包的构建过程中出现了错误。你可以查看两个日志文件来获取更详细的错误信息：`CMakeOutput.log`和`CMakeError.log`。

你可以使用以下命令来查看这些日志文件的内容：

```bash
cat /home/glider/workspace/catkin_workspace/build/CMakeFiles/CMakeOutput.log
cat /home/glider/workspace/catkin_workspace/build/CMakeFiles/CMakeError.log
```

这些日志文件将提供有关配置过程中发生的错误的详细信息，包括错误消息、警告和其他相关信息。

通过查看这些日志文件，你应该能够确定导致配置不完整和错误的具体原因。根据错误信息，你可以采取相应的措施来解决问题，例如修复依赖关系、安装缺少的软件包或调整构建配置。

如果你需要更具体的帮助，请提供相关的错误信息，我将尽力提供进一步的指导。

---
