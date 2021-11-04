#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <thread>
#include <Eigen/Core>

#include <pcl/point_cloud.h>
#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/segmentation/sac_segmentation.h>


#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/ndt.h> //ndt头文件
#include <pcl/registration/icp.h> //icp头文件
#include <boost/thread/thread.hpp>


using namespace std;
using namespace Eigen;


typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

// 预处理过程
void pretreat(PointCloud::Ptr & pcd_cloud, PointCloud::Ptr & pcd_down,float LeafSize=0.04) {
	//去除NAN点
	std::vector<int> indices_src; //保存去除的点的索引
	pcl::removeNaNFromPointCloud(*pcd_cloud, *pcd_cloud, indices_src);
	std::cout << "remove *cloud_source nan" << endl;
	//下采样滤波
	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
	voxel_grid.setLeafSize(LeafSize, LeafSize, LeafSize);
	voxel_grid.setInputCloud(pcd_cloud);
	voxel_grid.filter(*pcd_down);
	cout << "down size *cloud from " << pcd_cloud->size() << "to" << pcd_down->size() << endl;
};
// 点云可视化
void visualize_pcd(PointCloud::Ptr& pcd_src, PointCloud::Ptr& pcd_tgt, PointCloud::Ptr& pcd_final)
{
	pcl::visualization::PCLVisualizer viewer("registration Viewer");
	//原始点云绿色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> src_h(pcd_src, 0, 255, 0);
	//目标点云红色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> tgt_h(pcd_tgt, 255, 0, 0);
	//匹配好的点云蓝色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> final_h(pcd_final, 0, 0, 255);

	viewer.setBackgroundColor(255, 255, 255);
	viewer.setWindowName("NDT+ICP配准");
	viewer.addPointCloud(pcd_src, src_h, "source cloud");
	viewer.addPointCloud(pcd_tgt, tgt_h, "target cloud");
	viewer.addPointCloud(pcd_final, final_h, "result cloud");
	while (!viewer.wasStopped())
	{
		viewer.spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}

}
// 由旋转平移矩阵计算旋转角度
void matrix2angle(Eigen::Matrix4f &result_trans, Eigen::Vector3f &result_angle)
{
	double ax, ay, az;
	if (result_trans(2, 0) == 1 || result_trans(2, 0) == -1)
	{
		az = 0;
		double dlta;
		dlta = atan2(result_trans(0, 1), result_trans(0, 2));
		if (result_trans(2, 0) == -1)
		{
			ay = M_PI / 2;
			ax = az + dlta;
		}
		else
		{
			ay = -M_PI / 2;
			ax = -az + dlta;
		}
	}
	else
	{
		ay = -asin(result_trans(2, 0));
		ax = atan2(result_trans(2, 1) / cos(ay), result_trans(2, 2) / cos(ay));
		az = atan2(result_trans(1, 0) / cos(ay), result_trans(0, 0) / cos(ay));
	}
	result_angle << ax, ay, az;

	cout << "x轴旋转角度：" << ax << endl;
	cout << "y轴旋转角度：" << ay << endl;
	cout << "z轴旋转角度：" << az << endl;
}




//标准ICP
void test1() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>(5, 1));
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZ>);

    // Fill in the CloudIn data
    for (auto &point : *cloud_in) {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    std::cout << "Saved " << cloud_in->size()<< " data points to input:" << std::endl;

    for (auto &point : *cloud_in)
        std::cout << point << std::endl;

    *cloud_out = *cloud_in;

    std::cout << "size:" << cloud_out->size() << std::endl;
    for (auto &point : *cloud_out)
        point.x += 0.7f;

    std::cout << "Transformed " << cloud_in->size()<< " data points:" << std::endl;

    for (auto &point : *cloud_out)
        std::cout << point << std::endl;

    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_in);
    icp.setInputTarget(cloud_out);

    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);

    std::cout << "has converged:" << icp.hasConverged()<< " score: " << icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;
}

//正态分布变换（NDT）
void test2() {
    // Loading first scan of room.
    pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(
            "/home/admins/桌面/github/SubstrateDevelopment/data/point/"
            "room_scan1.pcd",
            *target_cloud) == -1) {
        PCL_ERROR("Couldn't read file room_scan1.pcd \n");
    }
    std::cout << "Loaded " << target_cloud->size()
              << " data points from room_scan1.pcd" << std::endl;

    // Loading second scan of room from new perspective.
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(
            "/home/admins/桌面/github/SubstrateDevelopment/data/point/"
            "room_scan2.pcd",
            *input_cloud) == -1) {
        PCL_ERROR("Couldn't read file room_scan2.pcd \n");
    }
    std::cout << "Loaded " << input_cloud->size()
              << " data points from room_scan2.pcd" << std::endl;

    // Filtering input scan to roughly 10% of original size to increase speed of
    // registration.
    pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ApproximateVoxelGrid<pcl::PointXYZ> approximate_voxel_filter;
    approximate_voxel_filter.setLeafSize(0.2, 0.2, 0.2);
    approximate_voxel_filter.setInputCloud(input_cloud);
    approximate_voxel_filter.filter(*filtered_cloud);
    std::cout << "Filtered cloud contains " << filtered_cloud->size()
              << " data points from room_scan2.pcd" << std::endl;

    // Initializing Normal Distributions Transform (NDT).
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;

    // Setting scale dependent NDT parameters
    // Setting minimum transformation difference for termination condition.
    ndt.setTransformationEpsilon(0.01);
    // Setting maximum step size for More-Thuente line search.
    ndt.setStepSize(0.1);
    // Setting Resolution of NDT grid structure (VoxelGridCovariance).
    ndt.setResolution(1.0);

    // Setting max number of registration iterations.
    ndt.setMaximumIterations(35);

    // Setting point cloud to be aligned.
    ndt.setInputSource(filtered_cloud);
    // Setting point cloud to be aligned to.
    ndt.setInputTarget(target_cloud);

    // Set initial alignment estimate found using robot odometry.
    Eigen::AngleAxisf init_rotation(0.6931, Eigen::Vector3f::UnitZ());
    Eigen::Translation3f init_translation(1.79387, 0.720047, 0);
    Eigen::Matrix4f init_guess = (init_translation * init_rotation).matrix();

    // Calculating required rigid transform to align the input cloud to the
    // target cloud.
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    ndt.align(*output_cloud, init_guess);

    std::cout << "Normal Distributions Transform has converged:"
              << ndt.hasConverged() << " score: " << ndt.getFitnessScore()
              << std::endl;

    // Transforming unfiltered, input cloud using found transform.
    pcl::transformPointCloud(*input_cloud, *output_cloud,
                             ndt.getFinalTransformation());

    // Saving transformed input cloud.
    pcl::io::savePCDFileASCII("room_scan2_transformed.pcd", *output_cloud);

    // Initializing point cloud visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer_final(
        new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer_final->setBackgroundColor(0, 0, 0);

    // Coloring and visualizing target cloud (red).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
        target_color(target_cloud, 255, 0, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(target_cloud, target_color,
                                               "target cloud");
    viewer_final->setPointCloudRenderingProperties(
        pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "target cloud");

    // Coloring and visualizing transformed input cloud (green).
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>
        output_color(output_cloud, 0, 255, 0);
    viewer_final->addPointCloud<pcl::PointXYZ>(output_cloud, output_color,
                                               "output cloud");
    viewer_final->setPointCloudRenderingProperties(
        pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "output cloud");

    // Starting visualizer
    viewer_final->addCoordinateSystem(1.0, "global");
    viewer_final->initCameraParameters();

    // Wait until visualizer window is closed.
    while (!viewer_final->wasStopped()) {
        viewer_final->spinOnce(100);
        // std::this_thread::sleep_for(100ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void test3(int argc, char **argv) {
    // Types
    typedef pcl::PointNormal PointNT;
    typedef pcl::PointCloud<PointNT> PointCloudT;
    typedef pcl::FPFHSignature33 FeatureT;
    typedef pcl::FPFHEstimationOMP<PointNT, PointNT, FeatureT> FeatureEstimationT;
    typedef pcl::PointCloud<FeatureT> FeatureCloudT;
    typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT>  ColorHandlerT;
    // Point clouds
    PointCloudT::Ptr object(new PointCloudT);
    PointCloudT::Ptr object_aligned(new PointCloudT);
    PointCloudT::Ptr scene(new PointCloudT);
    FeatureCloudT::Ptr object_features(new FeatureCloudT);
    FeatureCloudT::Ptr scene_features(new FeatureCloudT);

    // Get input object and scene
    if (argc != 3) {
        pcl::console::print_error("Syntax is: %s object.pcd scene.pcd\n", argv[0]);
    }

    // Load object and scene
    pcl::console::print_highlight("Loading point clouds...\n");
    if (pcl::io::loadPCDFile<PointNT>(argv[1], *object) < 0 ||
        pcl::io::loadPCDFile<PointNT>(argv[2], *scene) < 0) {
        pcl::console::print_error("Error loading object/scene file!\n");
    }

    // Downsample
    pcl::console::print_highlight("Downsampling...\n");
    pcl::VoxelGrid<PointNT> grid;
    const float leaf = 0.005f;
    grid.setLeafSize(leaf, leaf, leaf);
    grid.setInputCloud(object);
    grid.filter(*object);
    grid.setInputCloud(scene);
    grid.filter(*scene);

    // Estimate normals for scene
    pcl::console::print_highlight("Estimating scene normals...\n");
    pcl::NormalEstimationOMP<PointNT, PointNT> nest;
    nest.setRadiusSearch(0.01);
    nest.setInputCloud(scene);
    nest.compute(*scene);

    // Estimate features
    pcl::console::print_highlight("Estimating features...\n");
    FeatureEstimationT fest;
    fest.setRadiusSearch(0.025);
    fest.setInputCloud(object);
    fest.setInputNormals(object);
    fest.compute(*object_features);
    fest.setInputCloud(scene);
    fest.setInputNormals(scene);
    fest.compute(*scene_features);

    // Perform alignment
    pcl::console::print_highlight("Starting alignment...\n");
    pcl::SampleConsensusPrerejective<PointNT, PointNT, FeatureT> align;
    align.setInputSource(object);
    align.setSourceFeatures(object_features);
    align.setInputTarget(scene);
    align.setTargetFeatures(scene_features);
    align.setMaximumIterations(50000); // Number of RANSAC iterations
    align.setNumberOfSamples(
        3); // Number of points to sample for generating/prerejecting a pose
    align.setCorrespondenceRandomness(5); // Number of nearest features to use
    align.setSimilarityThreshold(
        0.9f); // Polygonal edge length similarity threshold
    align.setMaxCorrespondenceDistance(2.5f * leaf); // Inlier threshold
    align.setInlierFraction(
        0.25f); // Required inlier fraction for accepting a pose hypothesis
    {
        pcl::ScopeTime t("Alignment");
        align.align(*object_aligned);
    }

    if (align.hasConverged()) {
        // Print results
        printf("\n");
        Eigen::Matrix4f transformation = align.getFinalTransformation();
        pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n",
                                 transformation(0, 0), transformation(0, 1),
                                 transformation(0, 2));
        pcl::console::print_info("R = | %6.3f %6.3f %6.3f | \n",
                                 transformation(1, 0), transformation(1, 1),
                                 transformation(1, 2));
        pcl::console::print_info("    | %6.3f %6.3f %6.3f | \n",
                                 transformation(2, 0), transformation(2, 1),
                                 transformation(2, 2));
        pcl::console::print_info("\n");
        pcl::console::print_info("t = < %0.3f, %0.3f, %0.3f >\n",
                                 transformation(0, 3), transformation(1, 3),
                                 transformation(2, 3));
        pcl::console::print_info("\n");
        pcl::console::print_info("Inliers: %i/%i\n", align.getInliers().size(),
                                 object->size());

        // Show alignment
        pcl::visualization::PCLVisualizer visu("Alignment");
        visu.addPointCloud(scene, ColorHandlerT(scene, 0.0, 255.0, 0.0),
                           "scene");
        visu.addPointCloud(object_aligned,
                           ColorHandlerT(object_aligned, 0.0, 0.0, 255.0),
                           "object_aligned");
        visu.spin();
    } else {
        pcl::console::print_error("Alignment failed!\n");
    }
}

//NDT+ICP
void test4(int argc, char **argv){
    //创建点云指针
	PointCloud::Ptr cloud_source(new PointCloud);
	PointCloud::Ptr cloud_target(new PointCloud);
	// 加载点云文件
	// pcl::io::loadPCDFile("/home/admins/桌面/github/SubstrateDevelopment/data/point/"
    //         "chef.pcd", *cloud_source);
	// cout << "source loaded!" << endl;
	// pcl::io::loadPCDFile("/home/admins/桌面/github/SubstrateDevelopment/data/point/"
    //         "rs1.pcd", *cloud_target);
	// cout << "target loaded!" << endl;
    
    pcl::io::loadPLYFile("/home/admins/桌面/github/SubstrateDevelopment/data/point/"
            "tmp_tof_data_wire3567487.ply", *cloud_source);
	cout << "source loaded!" << endl;
	pcl::io::loadPLYFile("/home/admins/桌面/github/SubstrateDevelopment/data/point/"
            "tmp_tof_data_wire3571643.ply", *cloud_target);
	cout << "target loaded!" << endl;

	clock_t start = clock();

	PointCloud::Ptr cloud_src(new PointCloud);
	PointCloud::Ptr cloud_tar(new PointCloud);
	pretreat(cloud_source, cloud_src);
	pretreat(cloud_target, cloud_tar);
	//NDT配准
	pcl::NormalDistributionsTransform<PointT, PointT> ndt;
	PointCloud::Ptr cloud_ndt(new PointCloud);
	
	ndt.setInputSource(cloud_src);
	ndt.setInputTarget(cloud_tar);
	
	ndt.setStepSize(0.5);              // 为More-Thuente线搜索设置最大步长
	ndt.setResolution(2);              // 设置NDT网格结构的分辨率（VoxelGridCovariance）
	ndt.setMaximumIterations(35);      // 设置匹配迭代的最大次数
	ndt.setTransformationEpsilon(0.01);// 为终止条件设置最小转换差异
	ndt.align(*cloud_ndt);       

	clock_t ndt_t = clock();
	cout << "ndt time" << (double)(ndt_t - start) / CLOCKS_PER_SEC << endl;

	Eigen::Matrix4f ndt_trans = ndt.getFinalTransformation();
	
	//icp配准算法
	pcl::IterativeClosestPoint<PointT, PointT> icp;
	PointCloud::Ptr cloud_icp_registration(new PointCloud);
	//设置参数
	icp.setInputSource(cloud_src);
	icp.setInputTarget(cloud_tar);
	icp.setMaxCorrespondenceDistance(10);
	icp.setTransformationEpsilon(1e-10);
	icp.setEuclideanFitnessEpsilon(0.1);
	icp.setMaximumIterations(50);
	icp.align(*cloud_icp_registration, ndt_trans);

	clock_t end = clock();

	cout << "icp time" << (double)(end - ndt_t) / CLOCKS_PER_SEC << endl;
	cout << "total time" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	Eigen::Matrix4f icp_trans = icp.getFinalTransformation();
	cout << icp_trans << endl;

	pcl::transformPointCloud(*cloud_source, *cloud_icp_registration, icp_trans);

	//计算误差
	Eigen::Vector3f ANGLE_origin;
	Eigen::Vector3f TRANS_origin;
	ANGLE_origin << 0, 0, M_PI / 4;
	TRANS_origin << 0, 0.3, 0.2;
	double a_error_x, a_error_y, a_error_z;
	double t_error_x, t_error_y, t_error_z;
	Eigen::Vector3f ANGLE_result; // 由IMU得出的变换矩阵
	matrix2angle(icp_trans, ANGLE_result);
	a_error_x = fabs(ANGLE_result(0)) - fabs(ANGLE_origin(0));
	a_error_y = fabs(ANGLE_result(1)) - fabs(ANGLE_origin(1));
	a_error_z = fabs(ANGLE_result(2)) - fabs(ANGLE_origin(2));
	cout << "点云实际旋转角度:\n" << ANGLE_origin << endl;
	cout << "x轴旋转误差 : " << a_error_x << "  y轴旋转误差 : " << a_error_y << "  z轴旋转误差 : " << a_error_z << endl;

	cout << "点云实际平移距离:\n" << TRANS_origin << endl;
	t_error_x = fabs(icp_trans(0, 3)) - fabs(TRANS_origin(0));
	t_error_y = fabs(icp_trans(1, 3)) - fabs(TRANS_origin(1));
	t_error_z = fabs(icp_trans(2, 3)) - fabs(TRANS_origin(2));
	cout << "计算得到的平移距离" << endl << "x轴平移" << icp_trans(0, 3) << endl << "y轴平移" << icp_trans(1, 3) << endl << "z轴平移" << icp_trans(2, 3) << endl;
	cout << "x轴平移误差 : " << t_error_x << "  y轴平移误差 : " << t_error_y << "  z轴平移误差 : " << t_error_z << endl;
	//可视化
	visualize_pcd(cloud_source, cloud_target, cloud_icp_registration);
}



int main(int argc, char **argv) {
    // test2();
    test4(argc,argv);
    return (0);
}