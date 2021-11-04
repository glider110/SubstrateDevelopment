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
    string path="fawea";
    vector<PointCloud::Ptr> vecCloudPtr;
    vecCloudPtr=locator.read3DStream(path);
    // locator.inputPointcloud(cloud_source,cloud_target);
    locator.inputPointcloud(vecCloudPtr[0],vecCloudPtr[13]);
    // locator.computeTofPosition();
    // locator.visualize();
    int numFrame=vecCloudPtr.size();
    
     // 可视化相关
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    int frame = 0;
     pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud(new (pcl::PointCloud<pcl::PointXYZ>));
    auto display2 = [&]() {
        int v1 = 0;
        char buf[233];
        if (frame != 0) {
            sprintf(buf,"frame%d",frame);
            viewer->removePointCloud(buf);
        }
        sprintf(buf,"frame%d", ++frame);
        viewer->createViewPort(0.0, 0.0, 1.0, 1.0, v1);
        viewer->addPointCloud<pcl::PointXYZ> (point_cloud,buf);
        viewer->spinOnce();
    };     
    
    while (1)
    {
        for (size_t i = 0; i < numFrame; i++)
        {
        point_cloud=vecCloudPtr[i];
        display2();
        }
        
       
    }
    
    
    return (0);
}