# docker

解决什么问题?

- [ ] 独立与宿主机,可以有独立开发环境,也可以移植到其他linux机器上
- [ ] 今后的mac也不用担心开发环境了;



核心逻辑:

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly91c2VyLWdvbGQtY2RuLnhpdHUuaW8vMjAyMC8xLzQvMTZmNmUwYjM4MDVlNjAyNw?x-oss-process=image/format,png)





#### 重点操作和命令:

**下载镜像（测试用，找个小的镜像）**

```
docker pull busybox      //去官网拉去各种linux的发行版本
```

 **查看已下载的镜像**

```
docker images           //可以看做为一个类
```

**启动镜像变为容器**

```
docker run -d -it --name testbusybox busybox    //可以看做类的实例化 testbusybox实例化容器名
```

**查看已经启动的容器（镜像）**

```
docker ps
```
 **进入运行中的容器**

```
docker exec -it testbusybox /bin/sh
```



**docker操作**

```
groups 
 1969  docker exec -it ak_sdk /bin/bash
 1970  exit
 1971  docker compose up -d 
 1972  docker container ls -a
 1973  docker rm epic_bhabha quirky_burnell 
 1974  docker compose up -d 
 1975  docker container ls -a
 1976  docker exec -it ak_sdk /bin/bash
```

#### 参考:

[**1.docker入门**](https://www.cnblogs.com/aoeiuv/category/907475.html)

