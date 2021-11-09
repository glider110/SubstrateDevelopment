#include "../tofLocation/tofLocation.h"
// #include "tofLocation.h" #vscode读不到文件
using namespace std;
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;


int main(int argc, char **argv) {
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


    cout << "xxxxxxxx: " << cloud_source->size() << endl;
	NS_TOFLOCATION::tofLocation locator;
    locator.init();
    // string path=;
    vector<PointCloud::Ptr> vecCloudPtr;
    vecCloudPtr=locator.read3DStream("fawea");
    locator.inputPointcloud(cloud_source,cloud_target);
    locator.inputPointcloud(vecCloudPtr[2],vecCloudPtr[4]);
    locator.computeTofPosition();
    locator.visualize();
    
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
        viewer->addText("original", 10,10,"v1 text", v1);//设置视口名称
        viewer->createViewPort(0.5,0.0,1.0,1.0,v2);
        viewer->setBackgroundColor(0.3,0.3,0.3,v2);
        viewer->addText("after filtered", 10,10,"v2 text", v2);

        viewer->addPointCloud<pcl::PointXYZ>(point_cloud_src,buf_src,v1);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_tar,buf_tar,v1);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_tar,buf_tar_,v2);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud_reg,buf_reg,v2);
        viewer->spinOnce();
        boost::this_thread::sleep(boost::posix_time::microseconds(1000000));
    };     
    
    // while (1)
    // {
    //     for (size_t i = 0; i < vecCloudPtr.size()-1; i++)
    //     {
    //     cout << "ICP次数: " << i<< endl;
    //     point_cloud_src=vecCloudPtr[i];
    //     point_cloud_tar=vecCloudPtr[i+1];
    //    locator.inputPointcloud(point_cloud_src,point_cloud_tar);
    //    locator.computeTofPosition();
    //    point_cloud_reg=locator.getRegistratCloudPoint();
    //     display2();
        
    //     }
    // }
    
    
    return (0);
}