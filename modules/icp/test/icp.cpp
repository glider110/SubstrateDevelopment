#include"./icp.h"
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/correspondence_rejection_sample_consensus.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/transformation_estimation_lm.h>
#include <pcl/visualization/cloud_viewer.h>

pcl::PointCloud<pcl::PointNormal>::Ptr convert_to_pointnormal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
	pcl::PointCloud<pcl::Normal>::Ptr normal)
{
	pcl::PointCloud<pcl::PointNormal>::Ptr point_normal(new pcl::PointCloud<pcl::PointNormal>);
	pcl::PointNormal point_normal_temp;
	for (int i = 0; i < cloud->points.size(); ++i)
	{
		point_normal_temp.x = cloud->points[i].x;
		point_normal_temp.y = cloud->points[i].y;
		point_normal_temp.z = cloud->points[i].z;

		point_normal_temp.normal_x = normal->points[i].normal_x;
		point_normal_temp.normal_y = normal->points[i].normal_y;
		point_normal_temp.normal_z = normal->points[i].normal_z;
		point_normal->push_back(point_normal_temp);
	}
	return point_normal;
}

bool compute_normal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, 
	pcl::PointCloud<pcl::Normal>::Ptr normal)
{
	if (cloud == nullptr)
	{
		std::cout << "Normal data is null!\n";
		return false;
	}		
	///> compute normal 
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> cloud_normal;
	cloud_normal.setInputCloud(cloud);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
	cloud_normal.setSearchMethod(tree);
	cloud_normal.setKSearch(20);
	cloud_normal.compute(*normal);
	// if (false)
	// {
	// 	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	// 	viewer.setBackgroundColor(0.0, 0.0, 0.0);
	// 	viewer.addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, normal, 1, 0.05, "PCL Viewer");
	// 	while (!viewer.wasStopped())
	// 	{
	// 		viewer.spinOnce();
	// 	}
	// }
	return true;
}

bool iterative_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
	pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud,
	pcl::PointCloud<pcl::Normal>::Ptr source_normal,
	pcl::PointCloud<pcl::Normal>::Ptr target_normal,
	Eigen::Matrix4f& initial_transformation,
	Eigen::Matrix4f& finial_transformation)
{
	if (source_cloud == nullptr || source_cloud == nullptr || source_normal == nullptr || target_normal == nullptr)
	{
		std::cout << "Icp data is null!\n";
		return false;
	}
	std::cout << "Initial transformation:\n " << initial_transformation << std::endl;
	pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud_transformed(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::transformPointCloud(*source_cloud, *source_cloud_transformed, initial_transformation);
	pcl::PointCloud<pcl::PointNormal>::Ptr source_point_normal = convert_to_pointnormal(source_cloud_transformed, source_normal);
	pcl::PointCloud<pcl::PointNormal>::Ptr target_point_normal = convert_to_pointnormal(target_cloud, target_normal);
	pcl::IterativeClosestPointNonLinear<pcl::PointNormal, pcl::PointNormal> icp_lm;
	icp_lm.setInputSource(source_point_normal);
	icp_lm.setInputTarget(target_point_normal);
	icp_lm.setMaximumIterations(1000);
	icp_lm.setTransformationEpsilon(1e-6);
	icp_lm.setMaxCorrespondenceDistance(0.05);
	icp_lm.setEuclideanFitnessEpsilon(0.0001);
	pcl::PointCloud<pcl::PointNormal> Final;
	icp_lm.align(Final);
	if (!icp_lm.hasConverged())
	{
		std::cout << "Failed to icp!\n";
		return false;
	}
	finial_transformation = icp_lm.getFinalTransformation();
	std::cout << "\nfitness score:\t " << icp_lm.getFitnessScore() << std::endl;

	if (true)//debug_
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_transformed(new pcl::PointCloud<pcl::PointXYZ>);
		pcl::transformPointCloud(*source_cloud_transformed, *cloud_transformed, finial_transformation);
		pcl::PCDWriter w1,w2;
		w1.write("target_cloud.pcd", *target_cloud);
		w2.write("cloud_transformed.pcd", *cloud_transformed);
	}
	return true;
}

bool icp_pipline_test()
{		bool ret = false;
		///> source
		std::string root_path = "../source.pcd";
		pcl::PointCloud<pcl::PointXYZ> source_cloud;	
		pcl::PCDReader pcd_read;
		int status = pcd_read.read(root_path, source_cloud);
		if (status != 0)
		{
			std::cout << "Failed to read pcd file!\n";
			return ret;
		}
		
		///> target
		pcl::PointCloud<pcl::PointXYZ> target_cloud;
		Eigen::Matrix4f transformation;
		transformation << 0.9980, 0.0523, 0.0349, 1.000,
						                    -0.0552,  0.9947, 0.0871, 2.000,
					                    	-0.0302, 0.0889,  0.9956, 3.000,
					                    	0.0000,  0.0000,  0.0000,  1.0000;
		pcl::transformPointCloud(source_cloud, target_cloud, transformation);
		pcl::PCDWriter w3;
		w3.write("002.pcd", target_cloud);	
		transformation = Eigen::Matrix4f::Zero();
		
		// ///> normal
		// pcl::PointCloud<pcl::Normal>::Ptr source_normals(new pcl::PointCloud<pcl::Normal>), target_normals(new pcl::PointCloud<pcl::Normal>);
		// ret = compute_normal(source_cloud.makeShared(), source_normals);
		// if (!ret) return ret;
		// ret = compute_normal(target_cloud.makeShared(), target_normals);
		// if (!ret) return ret;
		
		// ///> initial transformation
		// Eigen::Matrix4f initial_transformation;
		// initial_transformation<<0.992731,  0.0703799, -0.0976327,    0.81838,
		// 		-0.0804302,   0.991409,  -0.103145,    1.75992,
		// 		0.0895346,   0.110248,   0.989863,     3.0017,
		// 		0,          0,          0,          1;
				
		// ///> icp
		// ret=iterative_closest_points(source_cloud.makeShared(),target_cloud.makeShared(),source_normals,target_normals,initial_transformation,transformation);
		// std::cout<<"final transformation:\t"<<transformation<<std::endl;

		return ret;
}