#include "tofLocation.h"
#include "cat.h"
using namespace NS_TOFLOCATION;



void NS_TOFLOCATION::tofLocation::init() {
    PointCloud::Ptr tmp_down_src(new PointCloud);
    PointCloud::Ptr tmp_down_tar(new PointCloud);
    m_down_tar=tmp_down_src;
    m_down_src=tmp_down_tar;
    //简化初始化
    mcloud_icp_registration=PointCloud::Ptr (new PointCloud);
    //初始化输出文件流
    mtofLog.open("../../config/output.txt",ios::app);
     //加载配置文件
    load_config("../../config/toflocation.yaml");
}

vector<PointCloud::Ptr>  NS_TOFLOCATION::tofLocation::read3DStream(string path)
{
    std::vector<cv::String> filenames; // notice here that we are using the Opencv's embedded "String" class
    cv::String folder = "/home/admins/akblib/ICP_DATA/workspace_log1/data"; // again we are using the Opencv's embedded "String" class

    cv::glob(folder, filenames); // new function that does the job ;-)
    vector<PointCloud::Ptr>  vec_path;
    for(size_t i = 0; i < filenames.size(); ++i)
    {
        // std::cout<<filenames[i]<<std::endl;
        PointCloud::Ptr cloud_target(new PointCloud);
        pcl::io::loadPLYFile(filenames[i],*cloud_target);
        vec_path.push_back(cloud_target);
    }
    return vec_path;
}

void NS_TOFLOCATION::tofLocation::inputPointcloud(PointCloud::Ptr cloud_source,PointCloud::Ptr cloud_target) 
{
    this->m_cloud_source=cloud_source;
    this->m_cloud_target=cloud_target;
    
}

void NS_TOFLOCATION::tofLocation::computeTofPosition()
{
    pretreat();
    registrationNDTWithICP();

}

void NS_TOFLOCATION::tofLocation::getTofPosition(){}

PointCloud::Ptr  NS_TOFLOCATION::tofLocation::getRegistratCloudPoint(){
    return mcloud_icp_registration;
}

void NS_TOFLOCATION::tofLocation::registrationNDTWithICP(){

//NDT配准
    clock_t start = clock();
	pcl::NormalDistributionsTransform<PointT, PointT> ndt;
	PointCloud::Ptr cloud_ndt(new PointCloud);	
	ndt.setInputSource(m_down_src);
	ndt.setInputTarget(m_down_tar);	
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
	//设置参数
	icp.setInputSource(m_down_src);
	icp.setInputTarget(m_down_tar);
	icp.setMaxCorrespondenceDistance(10);
	icp.setTransformationEpsilon(1e-10);
	icp.setEuclideanFitnessEpsilon(0.1);
	icp.setMaximumIterations(50);
	icp.align(*mcloud_icp_registration, ndt_trans);

    clock_t end = clock();
	cout << "icp time" << (double)(end - ndt_t) / CLOCKS_PER_SEC << endl;
	cout << "total time" << (double)(end - start) / CLOCKS_PER_SEC << endl;
	m_icp_trans = icp.getFinalTransformation();
	cout << m_icp_trans << endl;
    pcl::transformPointCloud(*m_cloud_source, *mcloud_icp_registration, m_icp_trans);
    Eigen::Vector3f ANGLE_result; // 由IMU得出的变换矩阵
	matrix2angle(m_icp_trans, ANGLE_result);
    cout << "计算得到的平移距离" << endl << "x轴平移" << m_icp_trans(0, 3) << endl << "y轴平移" << m_icp_trans(1, 3) << endl << "z轴平移" << m_icp_trans(2, 3) << endl;
}

void NS_TOFLOCATION::tofLocation::load_config(const string config_name)
{
    //  cv::FileStorage config("../../config/toflocation.yaml", cv::FileStorage::READ);
      cv::FileStorage config(config_name.c_str(), cv::FileStorage::READ);
      if (!config.isOpened())
      {
        cout<<"未读到配置文件..."<<endl;
        m_config.mLeafSize=0.04;
      }
      
      m_config.mLeafSize=(float)config["toflocation.mLeafSize"];
      cout<<"配置文件读取完毕..."<<endl;
      mtofLog<<"配置文件读取完毕..."<<endl;
}

// 预处理过程
void NS_TOFLOCATION::tofLocation::pretreat() {
	//去除NAN点
	std::vector<int> indices_src,indices_tar; //保存去除的点的索引
	pcl::removeNaNFromPointCloud(*m_cloud_source, *m_cloud_source, indices_src);
	pcl::removeNaNFromPointCloud(*m_cloud_target, *m_cloud_target, indices_tar);
	std::cout << "remove *cloud_source nan" << endl;
    cout << "原始数据src： " << m_cloud_source->size() << endl;
    cout << "原始数据tar： " << m_cloud_target->size() << endl;
	//直通滤波
	// pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_trans(new pcl::PointCloud<pcl::PointXYZ>);
    // cloud_trans=m_cloud_source;
	pcl::PassThrough<pcl::PointXYZ> pass_src,pass_tar;     //创建滤波器对象
	pass_src.setInputCloud(m_cloud_source);                //设置待滤波的点云
	pass_src.setFilterFieldName("y");             //设置在Z轴方向上进行滤波
	pass_src.setFilterLimits(0.01, 1);    //设置滤波范围(从最高点向下12米去除)
    pass_src.setFilterLimitsNegative(false);      //保留
	pass_src.filter(*m_cloud_source);               //滤波并存储
    pass_src.setInputCloud(m_cloud_source);                
    pass_src.setFilterFieldName("z");            
	pass_src.setFilterLimits(0.1, 1);   
    pass_src.setFilterLimitsNegative(false);     
	pass_src.filter(*m_cloud_source);               

    pass_tar.setInputCloud(m_cloud_target);              
	pass_tar.setFilterFieldName("y");            
	pass_tar.setFilterLimits(0.01, 1);     
	pass_tar.setFilterLimitsNegative(false);      
	pass_tar.filter(*m_cloud_target);  
    pass_tar.setInputCloud(m_cloud_target);              
    pass_tar.setFilterFieldName("z");            
	pass_tar.setFilterLimits(0.1, 1);   
	pass_tar.setFilterLimitsNegative(false);      
	pass_tar.filter(*m_cloud_target);                        
    cout << "cloud_src直通滤波后： " << m_cloud_source->size() << endl;
    cout <<" cloud_tar直通滤波后： "<< m_cloud_target->size() << endl;  
    //下采样滤波
	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid_src,voxel_grid_tar;
    cout << "LeafSize: " << m_config.mLeafSize<< endl;
    // cv::FileStorage config("../../config/toflocation.yaml", cv::FileStorage::READ);
    //  m_config.mLeafSize=(float)config["toflocation.setFilterLimits"];
	voxel_grid_src.setLeafSize( m_config.mLeafSize,  m_config.mLeafSize,  m_config.mLeafSize);
	voxel_grid_src.setInputCloud(m_cloud_source);	
	voxel_grid_src.filter(*m_down_src);
	voxel_grid_tar.setLeafSize( m_config.mLeafSize,  m_config.mLeafSize,  m_config.mLeafSize);
    voxel_grid_tar.setInputCloud(m_cloud_target);
	voxel_grid_tar.filter(*m_down_tar);
    cout << "LeafSize: " <<  m_config.mLeafSize << endl;

    cout << "cloud_src下采样后： " <<m_down_src->size() << endl;
    cout <<" cloud_tar下采样后： " << m_down_tar->size() << endl;  
};

NS_TOFLOCATION::tofLocation::~tofLocation()
{

}

// 点云可视化
void NS_TOFLOCATION::tofLocation::visualize()
{
	pcl::visualization::PCLVisualizer viewer("registration Viewer");
	//原始点云绿色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> src_h(m_cloud_source, 0, 255, 0);
	//目标点云红色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> tgt_h(m_cloud_target, 255, 0, 0);
	//匹配好的点云蓝色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> final_h(mcloud_icp_registration, 0, 0, 255);

	viewer.setBackgroundColor(255, 255, 255);
	viewer.setWindowName("NDT+ICP配准");
	viewer.addPointCloud(m_cloud_source, src_h, "source cloud");
	viewer.addPointCloud(m_cloud_target, tgt_h, "target cloud");
	viewer.addPointCloud(mcloud_icp_registration, final_h, "result cloud");
	while (!viewer.wasStopped())
	{
		viewer.spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}

}

// 由旋转平移矩阵计算旋转角度
void NS_TOFLOCATION::tofLocation::matrix2angle(Eigen::Matrix4f &result_trans, Eigen::Vector3f &result_angle)
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

