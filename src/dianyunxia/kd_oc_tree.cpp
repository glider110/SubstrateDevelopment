/*
 * @Description: https://www.cnblogs.com/li-yao7758258/p/6437440.html
 * @Author: HCQ
 * @Company(School): UCAS
 * @Email: 1756260160@qq.com
 * @Date: 2020-10-08 21:46:40
 * @LastEditTime: 2023-07-10 17:29:52
 * @FilePath: /SubstrateDevelopment/src/dianyunxia/kd_oc_tree.cpp
 */


#include <pcl/point_cloud.h>        //点类型定义头文件
#include <pcl/kdtree/kdtree_flann.h> //kdtree类定义头文件
#include <pcl/octree/octree.h>

#include <iostream>
#include <vector>
#include <ctime>

int
main (int argc, char** argv)
{
  srand (time (NULL));   //用系统时间初始化随机种子
  //创建一个PointCloud<pcl::PointXYZ>
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

  // 随机点云生成
  cloud->width = 1000;             //此处点云数量
  cloud->height = 1;                //表示点云为无序点云
  cloud->points.resize (cloud->width * cloud->height);

  for (size_t i = 0; i < cloud->points.size (); ++i)   //循环填充点云数据
  {
    cloud->points[i].x = 1024.0f * rand() / (RAND_MAX + 1.0f); // // 产生数值为0-1024的浮点数
    cloud->points[i].y = 1024.0f * rand () / (RAND_MAX + 1.0f);
    cloud->points[i].z = 1024.0f * rand () / (RAND_MAX + 1.0f);
  }
  {
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //创建KdTreeFLANN对象，并把创建的点云设置为输入,创建一个searchPoint变量作为查询点
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree; // pcl::KdTreeFLANN<PointT, Dist>::setInputCloud (const PointCloudConstPtr &cloud, const IndicesConstPtr &indices)
  //设置搜索空间
  kdtree.setInputCloud (cloud);
  //设置查询点并赋随机值
  pcl::PointXYZ searchPoint;
  searchPoint.x = 1024.0f * rand () / (RAND_MAX + 1.0f);
  searchPoint.y = 1024.0f * rand () / (RAND_MAX + 1.0f);
  searchPoint.z = 1024.0f * rand () / (RAND_MAX + 1.0f);

  // K 临近搜索
  //创建一个整数（设置为10）和两个向量来存储搜索到的K近邻，两个向量中，一个存储搜索到查询点近邻的索引，另一个存储对应近邻的距离平方
  int K = 10;

  std::vector<int> pointIdxNKNSearch(K);      //存储查询点近邻索引
  std::vector<float> pointNKNSquaredDistance(K); //存储近邻点对应距离平方
  //打印相关信息
  std::cout << "K nearest neighbor search at (" << searchPoint.x 
            << " " << searchPoint.y 
            << " " << searchPoint.z
            << ") with K=" << K << std::endl;

  if ( kdtree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )  //执行K近邻搜索
  {
     //打印所有近邻坐标
    for (size_t i = 0; i < pointIdxNKNSearch.size (); ++i)
      std::cout << "    "  <<   cloud->points[ pointIdxNKNSearch[i] ].x 
                << " " << cloud->points[ pointIdxNKNSearch[i] ].y 
                << " " << cloud->points[ pointIdxNKNSearch[i] ].z 
                << " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /**********************************************************************************
   下面的代码展示查找到给定的searchPoint的某一半径（随机产生）内所有近邻，重新定义两个向量
   pointIdxRadiusSearch  pointRadiusSquaredDistance来存储关于近邻的信息
   ********************************************************************************/
  // 半径 R内近邻搜索方法

  std::vector<int> pointIdxRadiusSearch;           //存储近邻索引
  std::vector<float> pointRadiusSquaredDistance;   //存储近邻对应距离的平方

  float radius = 256.0f * rand () / (RAND_MAX + 1.0f);   //随机的生成某一半径
  //打印输出
  std::cout << "Neighbors within radius search at (" << searchPoint.x 
            << " " << searchPoint.y 
            << " " << searchPoint.z
            << ") with radius=" << radius << std::endl;

  // 假设我们的kdtree返回了大于0个近邻。那么它将打印出在我们"searchPoint"附近的10个最近的邻居并把它们存到先前创立的向量中。
  if ( kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0 )  //执行半径R内近邻搜索方法
  {
    for (size_t i = 0; i < pointIdxRadiusSearch.size (); ++i)
      std::cout << "    "  <<   cloud->points[ pointIdxRadiusSearch[i] ].x 
                << " " << cloud->points[ pointIdxRadiusSearch[i] ].y 
                << " " << cloud->points[ pointIdxRadiusSearch[i] ].z 
                << " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
  }
  } // namespace kdtree
  


  /****************************************************************************
   创建一个octree实例，用设置分辨率进行初始化，该octree用它的页节点存放点索引向量，
   分辨率参数描述最低一级octree的最小体素的尺寸，因此octree的深度是分辨率和点云空间维度
   的函数，如果知道点云的边界框，应该用defineBoundingbox方法把它分配给octree然后通过
   点云指针把所有点增加到ctree中。
   *****************************************************************************/
    float resolution = 128.0f;

    pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution); //初始化Octree

    octree.setInputCloud(cloud);      //设置输入点云    这两句是最关键的建立PointCloud和octree之间的联系
    octree.addPointsFromInputCloud(); //构建octree

    pcl::PointXYZ searchPoint; //设置searchPoint

    searchPoint.x = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f * rand() / (RAND_MAX + 1.0f);
    searchPoint.z = 1024.0f * rand() / (RAND_MAX + 1.0f);

    /*************************************************************************************
  一旦PointCloud和octree联系一起，就能进行搜索操作，这里使用的是“体素近邻搜索”，把查询点所在体素中
   其他点的索引作为查询结果返回，结果以点索引向量的形式保存，因此搜索点和搜索结果之间的距离取决于octree的分辨率参数
*****************************************************************************************/

    std::vector<int> pointIdxVec; //存储体素近邻搜索结果向量

    if (octree.voxelSearch(searchPoint, pointIdxVec)) //执行搜索，返回结果到pointIdxVec
    {
        std::cout << "Neighbors within voxel search at (" << searchPoint.x
                  << " " << searchPoint.y
                  << " " << searchPoint.z << ")"
                  << std::endl;

        for (size_t i = 0; i < pointIdxVec.size(); ++i) //打印结果点坐标
            std::cout << "    " << cloud->points[pointIdxVec[i]].x
                      << " " << cloud->points[pointIdxVec[i]].y
                      << " " << cloud->points[pointIdxVec[i]].z << std::endl;
    }

    /**********************************************************************************
  K 被设置为10 ，K近邻搜索  方法把搜索结果写到两个分开的向量，第一个pointIdxNKNSearch包含搜索结果
   （结果点的索引的向量）  第二个向量pointNKNSquaredDistance存储搜索点与近邻之间的距离的平方。
*************************************************************************************/
    //K 近邻搜索
    int K = 10;

    std::vector<int> pointIdxNKNSearch;         //结果点的索引的向量
    std::vector<float> pointNKNSquaredDistance; //搜索点与近邻之间的距离的平方

    std::cout << "K nearest neighbor search at (" << searchPoint.x
              << " " << searchPoint.y
              << " " << searchPoint.z
              << ") with K=" << K << std::endl;

    if (octree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
    {
        for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
            std::cout << "    " << cloud->points[pointIdxNKNSearch[i]].x
                      << " " << cloud->points[pointIdxNKNSearch[i]].y
                      << " " << cloud->points[pointIdxNKNSearch[i]].z
                      << " (squared distance: " << pointNKNSquaredDistance[i] << ")" << std::endl;
    }

    // 半径内近邻搜索

    std::vector<int> pointIdxRadiusSearch;
    std::vector<float> pointRadiusSquaredDistance;

    float radius = 256.0f * rand() / (RAND_MAX + 1.0f);

    std::cout << "Neighbors within radius search at (" << searchPoint.x
              << " " << searchPoint.y
              << " " << searchPoint.z
              << ") with radius=" << radius << std::endl;

    if (octree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
    {
        for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i)
            std::cout << "    " << cloud->points[pointIdxRadiusSearch[i]].x
                      << " " << cloud->points[pointIdxRadiusSearch[i]].y
                      << " " << cloud->points[pointIdxRadiusSearch[i]].z
                      << " (squared distance: " << pointRadiusSquaredDistance[i] << ")" << std::endl;
    }



  return 0;
}
