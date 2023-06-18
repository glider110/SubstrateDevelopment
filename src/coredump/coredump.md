#### [coredump配置](http://www.cppblog.com/jack-wang/archive/2020/09/15/217450.html)

* 查看是否开启转储
  ulimit -c
  输出为0表示未开启
* 开启转储：
  ulimit -c unlimited
  永久生效:打开 /etc/security/limits.conf文件    soft   core unlimited hard  core unlimited
* 查看当前转储文件路径：
  cat /proc/sys/kernel/core_pattern
* 设置转储文件路径:

    sudo bash -c 'echo "/home/admins/桌面/github/SubstrateDevelopment/coredump/corefile-%e" > /proc/sys/kernel/core_pattern'


    

* 编译程序

    gcc -ggdb3 -std=c99 -Wall -Wextra -pedantic -o main.out core.cpp

* 运行(如果coredump,生成对于core文件)

    main.out

* gdb调试

    gdb main.out corefile-main.out



**参考:**

1.http://www.cppblog.com/jack-wang/archive/2020/09/15/217450.html

2.https://blog.csdn.net/u012254599/article/details/125299282

3.https://www.cnblogs.com/whwywzhj/p/13272653.html
