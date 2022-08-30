#pragma once
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl/correspondence.h>
#include <pcl/point_representation.h>
#include<Eigen/Core>

pcl::PointCloud<pcl::PointNormal>::Ptr convert_to_pointnormal(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
	pcl::PointCloud<pcl::Normal>::Ptr source_normal);

bool compute_normal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
	pcl::PointCloud<pcl::Normal>::Ptr normal);

bool iterative_closest_points(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
	pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud,
	pcl::PointCloud<pcl::Normal>::Ptr source_normal,
	pcl::PointCloud<pcl::Normal>::Ptr target_normal,
	Eigen::Matrix4f& initial_transformation,
	Eigen::Matrix4f& finial_transformation);

bool icp_pipline_test();