/*
 * @Author: glider
 * @Date: 2023-07-06 20:39:02
 * @LastEditTime: 2023-07-06 23:12:35
 * @FilePath: /SubstrateDevelopment/src/dianyunxia/hull_extraction.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>  //RANSAC相关头文件
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/filters/project_inliers.h>  // 投影滤波 
#include <pcl/surface/concave_hull.h>
#include <pcl/geometry/planar_polygon.h>//定义多边形
#include <pcl/visualization/pcl_visualizer.h>


/* 流程概述
1.交易拟合最佳平面
2.将点云投影至拟合平面，形成平面点云
3.根据凸包算法提取二维点云的凸多边形边界 
*/

int main(int argc, char** argv)
{
    //--------------------------加载点云数据----------------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
          
    pcl::PCDReader reader;
    reader.read("/home/admins/project/SubstrateDevelopment/data/pcl/elephant.pcd", *cloud);
    std::cerr << "原始点云点的个数: " << cloud->points.size() << std::endl;
    //-------------------------RANSAC拟合平面---------------------------
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::SACSegmentation<pcl::PointXYZ> seg; 
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.01);
    seg.setInputCloud(cloud);
    seg.segment(*inliers, *coefficients);
    //-----------------------点云投影到平面----------------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_projected(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ProjectInliers<pcl::PointXYZ> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    proj.setInputCloud(cloud);
    proj.setModelCoefficients(coefficients);
    proj.filter(*cloud_projected);
    std::cerr << "投影后点的个数: "<< cloud_projected->points.size() << std::endl;
    pcl::PCDWriter writer;
    writer.write("投影点云.pcd", *cloud_projected, true);
    //---------------提取投影平面点云的凸多边形边界-------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_vex_hull(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ConvexHull<pcl::PointXYZ> hull;  //创建凸包对象
    hull.setInputCloud(cloud_projected);            //设置输入点云
    hull.setDimension(2);                 //设置输入数据的维度(2D)
    hull.reconstruct(*cloud_vex_hull);//计算2D凸包结果

    std::cerr << "凸多边形的点数: " << cloud_vex_hull->points.size() << std::endl;

    writer.write("凸多边形.pcd", *cloud_vex_hull, true);


 //---------------提取投影平面点云的凹多边形边界-------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_hull(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ConcaveHull<pcl::PointXYZ> chull;
    chull.setInputCloud(cloud_projected);
    chull.setAlpha(0.1);
    chull.reconstruct(*cloud_hull);

    std::cerr << "凹多边形的点数: " << cloud_hull->points.size() << std::endl;
    writer.write("凹多边形.pcd", *cloud_hull, true);


    //增加多边形
    pcl::PlanarPolygon<pcl::PointXYZ> polygon;
    pcl::PointCloud<pcl::PointXYZ> contour;
    contour.width = cloud_hull->width;
    contour.height = 1;
    contour.is_dense = false;
    contour.resize(contour.height * contour.width);

    for (size_t i = 0; i < cloud_hull->points.size(); ++i)
    {
        contour.points[i] = cloud_hull->points[i];

    }

    polygon.setContour(contour);
    float result = pcl::calculatePolygonArea(contour);
    cout << "多边形面积为：" << result << endl;
    pcl::visualization::PCLVisualizer viewer("Viewer");
    viewer.addPolygon(polygon, 255, 0, 0, "ploygon", 0);
    viewer.addPointCloud<pcl::PointXYZ>(cloud_hull, "sample cloud");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "sample cloud"); // 设置点云大小
    while (!viewer.wasStopped())
    {
        viewer.spinOnce(1);
    }

    return (0);
}
