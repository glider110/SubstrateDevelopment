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

    pcl::io::loadPLYFile(
        "/home/admins/桌面/github/SubstrateDevelopment/data/point/"
        "tmp_tof_data_wire3567487.ply",
        *cloud_source);
    cout << "source loaded!" << endl;
    pcl::io::loadPLYFile(
        "/home/admins/桌面/github/SubstrateDevelopment/data/point/"
        "tmp_tof_data_wire3571643.ply",
        *cloud_target);
    cout << "target loaded!" << endl;

    // cout << "xxxxxxxx: " << cloud_source->size() << endl;
    NS_TOFLOCATION::tofLocation locator;
    vector<PointCloud::Ptr> vecCloudPtr;
    locator.init();
    //序列点云匹配结果动态显示
    // locator.dynamicVisualization();

    //两帧对比可视化
    vecCloudPtr = locator.read3DStream("xxx");
    locator.inputPointcloud(cloud_source, cloud_target);
    locator.inputPointcloud(vecCloudPtr[2], vecCloudPtr[3]);
    locator.computeTofPosition();
    locator.visualize();
    return (0);
}