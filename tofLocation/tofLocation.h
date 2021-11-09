#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/approximate_voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <thread>
#include <Eigen/Core>
#include <pcl/filters/passthrough.h>  //直通滤波相关

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
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

namespace NS_TOFLOCATION
{
    typedef struct
    {
    float    mLeafSize;
    }TofLocationConfig;


    class tofLocation	
    {
    private:
        //测试log  
        TofLocationConfig m_config;  //输入配置参数表

        ofstream mtofLog;               //输出测试中间变量，可设置输出级别

        //参考点云的目标点云
        PointCloud::Ptr m_cloud_source,m_cloud_target,mcloud_icp_registration;
        PointCloud::Ptr m_down_tar;
        PointCloud::Ptr m_down_src;
        Eigen::Matrix4f m_icp_trans; 


        //点云预处理
        void pretreat();
        //加载参数表
        void loadConfigurationParameters();
        //小工具：变换矩阵to欧拉角
        void matrix2angle(Eigen::Matrix4f &result_trans, Eigen::Vector3f &result_angle);
        //NDT+ICP
        void registrationNDTWithICP();

        //加载配置文件
        void load_config(const string config_name);

    public:
        //初始化
        void init();

        //小工具：获取文件夹点云输出为数据流
        vector<PointCloud::Ptr> read3DStream(string path);

        void  inputPointcloud(PointCloud::Ptr cloud_source,PointCloud::Ptr cloud_target);

        void  inputImuPosition();

        void  computeTofPosition();

        void getTofPosition();

        PointCloud::Ptr  getRegistratCloudPoint();

        //点云可视化配准
        void visualize();
       
        ~tofLocation();
    };
} // namespace name



