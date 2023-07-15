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

