/*
 * @Author: glider
 * @Date: 2023-07-06 22:01:23
 * @LastEditTime: 2023-07-06 23:02:15
 * @FilePath: /SubstrateDevelopment/src/dianyunxia/main.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>//贪婪投影三角化算法类定义的头文件
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <vector>

//理解pcl::PolygonMesh  数据结构
void test1()
{
    std::vector<pcl::Vertices> polys;
    pcl::Vertices v1, v2;
    v1.vertices.push_back(0);
    v1.vertices.push_back(1);
    v1.vertices.push_back(2);
    v2.vertices.push_back(2);
    v2.vertices.push_back(3);
    v2.vertices.push_back(0);
    
    polys.push_back(v1);
    polys.push_back(v2);
    
    // pcl::PointXYZ pt0, pt1, pt2, pt3;
    //fill  pt0, pt1,..., pt3 with your values!
    pcl::PointXYZ pt0(0,0,0);
    pcl::PointXYZ pt1(1,0,0);
    pcl::PointXYZ pt2(0,1,0);
    pcl::PointXYZ pt3(0,0,1);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->push_back(pt0);
    cloud->push_back(pt1);
    cloud->push_back(pt2);
    cloud->push_back(pt3);
                        
    pcl::PolygonMesh mesh;
    mesh.polygons = polys;
    //convert cloud to blob
    pcl::PCLPointCloud2::Ptr cloud_blob(new pcl::PCLPointCloud2);
    pcl::toPCLPointCloud2(*cloud, *cloud_blob);
    
    mesh.cloud = *cloud_blob;
                        
    pcl::io::savePLYFile("cloud.ply", *cloud);
    pcl::io::savePLYFile("mesh.ply", mesh);
}




int main()
{
    test1();
    return 0;
}