/*
 * @Author: glider
 * @Date: 2023-07-11 12:58:58
 * @LastEditTime: 2023-07-11 22:06:01
 * @FilePath: /SubstrateDevelopment/src/dianyunxia/region_growing_segmentation.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */

# if 0
#include <vector>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/search/search.h>
#include <pcl/common/angles.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/segmentation/region_growing.h>//区域生长
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>

using namespace std;
using PointT = pcl::PointXYZRGB;

int
main(int argc, char** argv)
{
	// -------------------------------------------加载点云---------------------------------------------
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	if (pcl::io::loadPCDFile <PointT>("/home/admins/project/SubstrateDevelopment/data/pcl/data/tutorials/region_growing_tutorial.pcd", *cloud) == -1)
	{
		PCL_ERROR("Cloud reading failed.");
		return (-1);
	}
	//---------------------------------------法线和表面曲率估计---------------------------------------
	pcl::search::Search<PointT>::Ptr tree(new pcl::search::KdTree<PointT>);
	pcl::PointCloud <pcl::Normal>::Ptr normals(new pcl::PointCloud <pcl::Normal>);
	pcl::NormalEstimationOMP<PointT, pcl::Normal> n;
	n.setInputCloud(cloud);   // 设置法线估计对象输入点集
	n.setSearchMethod(tree);  // 设置搜索方法
	n.setNumberOfThreads(6);  // 设置openMP的线程数
	n.setKSearch(20);         // 设置用于法向量估计的k近邻数目
	n.compute(*normals);      // 计算并输出法向量

	//--------------------------------------------区域生长-------------------------------------------
	pcl::RegionGrowing<PointT, pcl::Normal> reg;
	reg.setMinClusterSize(100);                         // 一个聚类需要的最小点数
	reg.setMaxClusterSize(1000000);                    // 一个聚类需要的最大点数
	reg.setSearchMethod(tree);                         // 搜索方法
	reg.setNumberOfNeighbours(30);                     // 搜索的邻域点的个数
	reg.setInputCloud(cloud);                          // 输入点云
	reg.setInputNormals(normals);                      // 输入的法线
	reg.setSmoothnessThreshold(pcl::deg2rad(1.0));     // 设置平滑阈值，即法向量夹角的阈值(这里的3.0是角度制)
	reg.setCurvatureThreshold(3.0);                    // 设置曲率的阈值

	std::vector <pcl::PointIndices> clusters;
	reg.extract(clusters);                             // 获取聚类的结果，分割结果保存在点云索引的向量中。

	std::cout << "区域生长的聚类个数为：" << clusters.size() << std::endl;        // 输出聚类的数量
	std::cout << "第一个聚类里边有" << clusters[0].indices.size() << " 个点。" << endl; // 输出第一个聚类的数量

	//----------------------------------------保存聚类的点云----------------------------------------
	int begin = 0;
	for (std::vector<pcl::PointIndices>::const_iterator it = clusters.begin(); it != clusters.end(); ++it)
	{
		pcl::PointCloud<PointT>::Ptr cloud_cluster(new pcl::PointCloud<PointT>);

		for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); pit++)

			cloud_cluster->points.push_back(cloud->points[*pit]);
		cloud_cluster->width = cloud_cluster->points.size();
		cloud_cluster->height = 1;
		cloud_cluster->is_dense = true;

		std::cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size() << " data points."
			<< std::endl;
		std::stringstream ss;
		ss << "RegionGrowing_cluster_" << begin + 1 << ".pcd";
		pcl::io::savePCDFileBinary(ss.str(), *cloud_cluster);
		cout << ss.str() << "Saved" << endl;
		begin++;
	}

	pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();
	// 保存附加颜色的点云，这里保存的结果仍然是一整块点云
	pcl::io::savePCDFileBinary("colored_pointCloud.pcd", *colored_cloud);
	// -----------------------------------------------结果可视化-----------------------------------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(colored_cloud);// 显示RGB
	viewer->setWindowName("区域生长分割");
	viewer->addPointCloud<pcl::PointXYZRGB>(colored_cloud, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud"); // 设置点云大小

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}

	return 0;

}

#else


#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>       // 根据索引提取点云
#include <pcl/filters/voxel_grid.h>            // 体素滤波
#include <pcl/kdtree/kdtree.h>                 // kd树
#include <pcl/sample_consensus/method_types.h> // 采样方法
#include <pcl/sample_consensus/model_types.h>  // 采样模型
#include <pcl/ModelCoefficients.h>             // 模型系数
#include <pcl/segmentation/sac_segmentation.h> // 随机采样分割
#include <pcl/segmentation/extract_clusters.h> // 欧式聚类分割
#include <pcl/visualization/pcl_visualizer.h> 
#include <boost/thread/thread.hpp>

using namespace std;

int
main(int argc, char** argv)
{
    //--------------------------读取桌面场景点云---------------------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile<pcl::PointXYZ>("/home/admins/project/SubstrateDevelopment/data/pcl/data/tutorials/table_scene_lms400.pcd", *cloud);
    cout << "读取点云: " << cloud->points.size() << " 个." << endl;

    //---------------------------体素滤波下采样----------------------------------
    pcl::VoxelGrid<pcl::PointXYZ> vg;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    vg.setInputCloud(cloud);
    vg.setLeafSize(0.01f, 0.01f, 0.01f);
    vg.filter(*cloud_filtered);
    cout << "体素滤波后还有: " << cloud_filtered->points.size() << " 个." << endl;

    //--------------------创建平面模型分割的对象并设置参数-----------------------
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>);
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);    // 分割模型,平面模型
    seg.setMethodType(pcl::SAC_RANSAC);       // 参数估计方法,随机采样一致性　
    seg.setMaxIterations(100);                // 最大的迭代的次数
    seg.setDistanceThreshold(0.02);           // 设置符合模型的内点阈值

    // -------------模型分割,直到剩余点云数量在30%以上,确保模型点云较好----------
    int i = 0, nr_points = (int)cloud_filtered->points.size();// 下采样前点云数量
    while (cloud_filtered->points.size() > 0.3 * nr_points)

    {
        seg.setInputCloud(cloud_filtered);
        seg.segment(*inliers, *coefficients);// 分割
        if (inliers->indices.size() == 0)
        {
            cout << "Could not estimate a planar model for the given dataset." << endl;
            break;
        }
        //---------------------------根据索引提取点云-------------------------------
        pcl::ExtractIndices<pcl::PointXYZ> extract;
        extract.setInputCloud(cloud_filtered);
        extract.setIndices(inliers);         // 提取符合平面模型的内点
        extract.setNegative(false);
        //--------------------------平面模型内点------------------------------------
        extract.filter(*cloud_plane);
        cout << "平面模型: " << cloud_plane->points.size() << "个点." << endl;
        //-------------------移去平面局内点，提取剩余点云---------------------------
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
        extract.setNegative(true);
        extract.filter(*cloud_f);
        *cloud_filtered = *cloud_f;         // 剩余点云
    }

    // --------------桌子平面上的点云团,　使用欧式聚类的算法对点云聚类分割----------
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud_filtered);              // 桌子平面上其他的点云
    vector<pcl::PointIndices> cluster_indices;        // 点云团索引
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;// 欧式聚类对象
    ec.setClusterTolerance(0.02);                     // 设置近邻搜索的搜索半径为2cm（也即两个不同聚类团点之间的最小欧氏距离）
    ec.setMinClusterSize(100);                        // 设置一个聚类需要的最少的点数目为100
    ec.setMaxClusterSize(25000);                      // 设置一个聚类需要的最大点数目为25000
    ec.setSearchMethod(tree);                         // 设置点云的搜索机制
    ec.setInputCloud(cloud_filtered);
    ec.extract(cluster_indices);                      // 从点云中提取聚类，并将点云索引保存在cluster_indices中
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster_all(new pcl::PointCloud<pcl::PointXYZ>);
    //------------迭代访问点云索引cluster_indices,直到分割处所有聚类---------------
    int j = 0;
    for (vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        //创建新的点云数据集cloud_cluster，将所有当前聚类写入到点云数据集中
        for (vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit)
            cloud_cluster->points.push_back(cloud_filtered->points[*pit]); //获取每一个点云团的点

        cloud_cluster->width = cloud_cluster->points.size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size() << " data points." << endl;
        stringstream ss;
        ss << "cloud_cluster_" << j << ".pcd";
        pcl::PCDWriter writer;
        writer.write<pcl::PointXYZ>(ss.str(), *cloud_cluster, false);
        j++;

        *cloud_cluster_all += *cloud_cluster;
    }
    pcl::io::savePCDFileASCII("cloud_cluster_all.pcd", *cloud_cluster_all);

    //------------------------点云显示------------------------------------
    pcl::visualization::PCLVisualizer viewer("3D Viewer");
    viewer.setBackgroundColor(0, 0, 0);
    //viewer.addCoordinateSystem (1.0);
    viewer.initCameraParameters();
    //--------------------平面上的点云　红色------------------------------
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_plane_handler(cloud_plane, 255, 0, 0);
    viewer.addPointCloud(cloud_plane, cloud_plane_handler, "plan point");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "plan point");

    //--------------------平面外的点云　绿色------------------------------
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_cluster_handler(cloud_cluster_all, 0, 255, 0);
    viewer.addPointCloud(cloud_cluster_all, cloud_cluster_handler, "cloud_cluster point");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud_cluster point");

    while (!viewer.wasStopped()) {
        viewer.spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
    return (0);
}

#endif