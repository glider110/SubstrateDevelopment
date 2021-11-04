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
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

namespace NS_TOFLOCATION
{

    class tofLocation
	
    {
    private:
        //参考点云的目标点云
        PointCloud::Ptr m_cloud_source,m_cloud_target,mcloud_icp_registration;
        PointCloud::Ptr m_down_tar;
        PointCloud::Ptr m_down_src;
        Eigen::Matrix4f m_icp_trans; 
        //体素滤波间隔（米）
        float LeafSize=0.04;


        //点云预处理
        void pretreat();
        //加载参数表
        void loadConfigurationParameters();
        //小工具：变换矩阵to欧拉角
        void matrix2angle(Eigen::Matrix4f &result_trans, Eigen::Vector3f &result_angle);
        //NDT+ICP
        void registrationNDTWithICP();

    public:
        //初始化
        void init();

        //小工具：获取文件夹点云输出为数据流
        vector<PointCloud::Ptr> read3DStream(string path);

        void  inputPointcloud(PointCloud::Ptr cloud_source,PointCloud::Ptr cloud_target);

        void  inputImuPosition();

        void  computeTofPosition();

        void outputTofPosition();

        //点云可视化配准
        void visualize();
       
        ~tofLocation();
    };
} // namespace name



