#include "tofLocation.h"
#include "cat.h"
using namespace NS_TOFLOCATION;


void NS_TOFLOCATION::tofLocation::init() {

    cout << "************************"<< endl;
    cout << "*****TOFLOCATION*****"<< endl;
    cout << "************************"<< endl;
    PointCloud::Ptr tmp_down_src(new PointCloud);
    PointCloud::Ptr tmp_down_tar(new PointCloud);
    m_down_tar=tmp_down_src;
    m_down_src=tmp_down_tar;
    //简化初始化
    mcloud_icp_registration=PointCloud::Ptr (new PointCloud);

    // m_multrans=Eigen::Matrix4f::Identity();
    //初始化输出文件流
    mtofLog.open("../../config/output.txt",ios::app);
    fout.open("../../config/location.txt");
     //加载配置文件
    load_config("../../config/toflocation.yaml");
}

vector<PointCloud::Ptr>  NS_TOFLOCATION::tofLocation::read3DStream(string path)
{
    std::vector<cv::String> filenames;
    cv::String folder = "/home/admins/akblib/ICP_DATA/workspace_log11.11/data"; 
    cv::glob(folder, filenames); 
    vector<PointCloud::Ptr>  vec_path;
    for(size_t i = 0; i < filenames.size(); ++i)
    {
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

void NS_TOFLOCATION::tofLocation::getTofPosition()
{
    
}

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
    pcl::transformPointCloud(*m_cloud_source, *mcloud_icp_registration, m_icp_trans);
    Eigen::Vector3f ANGLE_result; // 由IMU得出的变换矩阵
	matrix2angle(m_icp_trans, ANGLE_result);
    cout <<"before:\n"<< m_multrans << endl;
    m_multrans*=m_icp_trans;
    cout << m_icp_trans << endl;
    cout <<"after:\n"<< m_multrans << endl;
    m_trck_point.push_back(pcl::PointXYZ(m_multrans(0,3),m_multrans(1,3),m_multrans(2,3)));
    fout << m_multrans(0,3)<<" "<<m_multrans(1,3)<<" "<<m_multrans(2,3) << endl;
    cout <<"轨迹点:\n"<< pcl::PointXYZ(m_multrans(0,3),m_multrans(1,3),m_multrans(2,3)) << endl;
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

void NS_TOFLOCATION::tofLocation::pretreat() {
	//去除NAN点
	std::vector<int> indices_src,indices_tar; //保存去除的点的索引
	pcl::removeNaNFromPointCloud(*m_cloud_source, *m_cloud_source, indices_src);
	pcl::removeNaNFromPointCloud(*m_cloud_target, *m_cloud_target, indices_tar);
	std::cout << "remove *cloud_source nan" << endl;
    cout << "原始数据src： " << m_cloud_source->size() << endl;
    cout << "原始数据tar： " << m_cloud_target->size() << endl;
	//直通滤波
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
	//统计滤波处理
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor_src,sor_tar;
    PointCloud::Ptr copypointsrc(new PointCloud);
    pcl::copyPointCloud(*m_cloud_source,*copypointsrc);
    PointCloud::Ptr copypointtar(new PointCloud);
    pcl::copyPointCloud(*m_cloud_target,*copypointtar);
    sor_src.setInputCloud (m_cloud_source);   //设置待滤波的点云
    sor_src.setMeanK (50);           //设置在进行统计时考虑查询点邻近点数
    sor_src.setStddevMulThresh (1);  //设置判断是否为离群点的阈值，里边的数字表示标准差的倍数，1个标准差以上就是离群点。
    sor_src.filter (*m_cloud_source); //存储内点
    sor_tar.setInputCloud (m_cloud_target);   //设置待滤波的点云
    sor_tar.setMeanK (50);           //设置在进行统计时考虑查询点邻近点数
    sor_tar.setStddevMulThresh (1);  //设置判断是否为离群点的阈值，里边的数字表示标准差的倍数，1个标准差以上就是离群点。
    sor_tar.filter (*m_cloud_target); //存储内点
    cout << "cloud_src统计滤波后：" <<  m_cloud_source->size()  << endl;
    cout << "cloud_tar统计滤波后：" <<  m_cloud_target->size()  << endl;
    // VisualizeCloud(m_cloud_source,copypointsrc);
    // VisualizeCloud(m_cloud_target,copypointtar);

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
 mtofLog.close();
 fout.close();//完成后，关闭TXT文件
}

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

void NS_TOFLOCATION::tofLocation::dynamicVisualization(){
     // 可视化相关
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    int frame = 0;
     pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_src(new (pcl::PointCloud<pcl::PointXYZ>));
     pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_tar(new (pcl::PointCloud<pcl::PointXYZ>));
     pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_reg(new (pcl::PointCloud<pcl::PointXYZ>));
    	//原始点云绿色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> src_h(point_cloud_src, 0, 255, 0);
	//目标点云红色
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> tgt_h(point_cloud_tar, 255, 0, 0);
    
    auto display2 = [&]() {
        
        char buf_src[233];
        char buf_tar[233];
        char buf_tar_[233];
        char buf_reg[233];
        if (frame != 0) {
            sprintf(buf_src,"frame%d",frame);
            viewer->removePointCloud(buf_src);
            viewer->removePointCloud(buf_tar);
            viewer->removePointCloud(buf_tar_);
            viewer->removePointCloud(buf_reg);
        }
        sprintf(buf_src,"frame%d", ++frame);
        sprintf(buf_tar,"frame%d", ++frame);
        sprintf(buf_tar_,"frame%d", ++frame);
        sprintf(buf_reg,"frame%d", ++frame);
        // viewer->createViewPort(0.0, 0.0, 1.0, 1.0, v1);
        int v1(0),v2(0);
        viewer->createViewPort(0.0,0.0,0.5,1.0,v1);//(Xmin,Ymin,Xmax,Ymax)设置窗口坐标
        // viewer->addText("original", 10,10,"v1 text", v1);//设置视口名称
        viewer->createViewPort(0.5,0.0,1.0,1.0,v2);
        viewer->setBackgroundColor(0.3,0.3,0.3,v2);
        // viewer->addText("after filtered", 10,10,"v2 text", v2);

        viewer->addPointCloud<pcl::PointXYZ>(point_cloud_src,buf_src,v1);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_tar,buf_tar,v1);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_tar,buf_tar_,v2);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_reg,buf_reg,v2);
        viewer->spinOnce();
        boost::this_thread::sleep(boost::posix_time::microseconds(1000000));
    };     
    vector<PointCloud::Ptr> vecCloudPtr;
    vecCloudPtr=read3DStream("fawea");
    while (1)
    {
        for (size_t i = 0; i < vecCloudPtr.size()-1; i++)
        {
        cout << "ICP次数: " << i<< endl;
        point_cloud_src=vecCloudPtr[i];
        point_cloud_tar=vecCloudPtr[i+1];
        this->inputPointcloud(point_cloud_src,point_cloud_tar);
        this->computeTofPosition();
       point_cloud_reg=this->getRegistratCloudPoint();
        display2();
        
        }
        break;
    }
    
    

}

 void NS_TOFLOCATION::tofLocation::VisualizeCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& filter_cloud)
 {
     //-----------------------显示点云-----------------------
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("显示点云"));

    int v1(0), v2(0);
    viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
    viewer->setBackgroundColor(0, 0, 0, v1);
    viewer->addText("point clouds", 10, 10, "v1_text", v1);
    viewer->createViewPort(0.5, 0.0, 1, 1.0, v2);
    viewer->setBackgroundColor(0.1, 0.1, 0.1, v2);
    viewer->addText("filtered point clouds", 10, 10, "v2_text", v2);
    // 按照z字段进行渲染,将z改为x或y即为按照x或y字段渲染
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z");
    pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildfilterColor(filter_cloud, "z");
    viewer->addPointCloud<pcl::PointXYZ>(cloud, fildColor, "sample cloud", v1);

    viewer->addPointCloud<pcl::PointXYZ>(filter_cloud,fildfilterColor, "cloud_filtered", v2);
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 0, "cloud_filtered", v2);
    //viewer->addCoordinateSystem(1.0);
    //viewer->initCameraParameters();
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
}
 
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

	cout << "x轴旋转角度：" << ax*180/3.141<< endl;
	cout << "y轴旋转角度：" << ay*180/3.141 << endl;
	cout << "z轴旋转角度：" << az*180/3.141 << endl;
}

