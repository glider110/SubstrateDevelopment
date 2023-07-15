## PCL学习

#### 文件格式

.pcd

.stl

.ply

![image-20230706205826907](pcl.assets/image-20230706205826907.png)

.mesh

.obj

.las  

LAS格式是一种二进制文件格式。其目的是提供一种开放的格式标准,允许不同的硬件和软件提供商输出可互操作的统一格式。现在LAS格式文件已成为LiDAR数据的工业标准格式.LAS文件按每条扫描线排列方式存放数据,包括激光点的三维坐标、多次回波信息、强度信息、扫描角度、分类信息、飞行航带信息、飞行姿态信息、项目信息、GPS信息、数据点颜色信息等





#### **二叉树**

![image-20230710155423428](pcl_learn/image-20230710155423428.png)

![image-20230710155455502](pcl_learn/image-20230710155455502.png)



#### [**octree**](https://blog.csdn.net/m0_37816922/article/details/124792692)

八叉树(octree)是一种空间中的栅格化方法，为了更直观地理解八叉树的思想，可通过其二维形式——四叉树来进行说明。仍以六个数据点作为研究对象：{(2,3), (5,4), (9,6), (4,7), (8,1), (7,2)}，如果以[ 0 , 10 ) [0,10)[0,10)为坐标空间，那么通过对这个空间四等分，可得到下左图
<img src="https://img-blog.csdnimg.cn/a839c2d7868d47df918344b4c88dd81e.png#pic_center" alt="在这里插入图片描述" style="zoom:67%;" /><img src="https://img-blog.csdnimg.cn/7655b49f6a8d40aa978ba0db70a464a8.png#pic_center" alt="在这里插入图片描述" style="zoom:67%;" />









最小二乘拟合，旨在照顾所有人的想法，对所有数据进行拟合，在无效数据多且偏移量大的情况下，拟合效果不好。
而RANSAC拟合，旨在照顾多数人的意愿，对主体数据进行拟合，手动设置一个阈值，同拟合平面的距离超过阈值的点，就被判定为无效数据。
随机拟合多个平面，选取平面内数据点最多的平面，或者说，无效数据最少的平面，作为拟合出的结果。

![img](https://img-blog.csdnimg.cn/20181130130729575.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE4OTQxNzEz,size_16,color_FFFFFF,t_70)

  







  `pcl::copyPointCloud(*cloud, inliers, *final);`



**欧式距离分割**

![image-20230711215155540](pcl_learn/image-20230711215155540.png)



**区域生长分割**

![image-20230711215110248](pcl_learn/image-20230711215110248.png)



**点云特征**

- [ ] 法向量 :PCA分析和最小二乘拟合平面获取

  PCA的协方差矩阵分解的特征值最小值对应的向量就是法向量

- [ ] 曲率

  ![image-20230714100414806](pcl_learn/image-20230714100414806.png)

