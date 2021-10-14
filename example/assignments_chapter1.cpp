#include "iostream"
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <pcl/common/common_headers.h>
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h> //kdtree近邻搜索
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/PolygonMesh.h>
#include <pcl/io/vtk_lib_io.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h> //pcd 读写类相关的头文件。
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h> //PCL中支持的点类型头文件。
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <vector>

using namespace std;
using namespace Eigen;
using namespace pcl;
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;


void eigen_value_(PointCloud<PointT>::Ptr cloud,
                  vector<vector<int>> point_neighbours, int K_nebor,
                  MatrixXf &eigen_value, MatrixXf &line_, MatrixXf &plane_,
                  MatrixXf &Sphericity) {
    eigen_value = MatrixXf::Zero(cloud->size(), 3);
    line_.resize(cloud->size(), 1);
    plane_.resize(cloud->size(), 1);
    Sphericity.resize(cloud->size(), 1);
    Matrix<float, 3, 3> covariance_matrix;
    Matrix<float, 3, 1> centroid_;
    Matrix<float, 3, 1> tem_;
    for (int i_point = 0; i_point < cloud->size(); i_point++) {
        tem_.setZero();
        centroid_.setZero();
        covariance_matrix.setZero();
        for (int i_nebor_point = 0; i_nebor_point < K_nebor; i_nebor_point++) {
            centroid_[0] +=
                cloud->points[point_neighbours[i_point][i_nebor_point]].x;
            centroid_[1] +=
                cloud->points[point_neighbours[i_point][i_nebor_point]].y;
            centroid_[2] +=
                cloud->points[point_neighbours[i_point][i_nebor_point]].z;
        }
        centroid_ /= K_nebor;
        for (int i_nebor = 0; i_nebor < K_nebor; i_nebor++) {
            tem_[0] = cloud->points[point_neighbours[i_point][i_nebor]].x -
                      centroid_[0];
            tem_[1] = cloud->points[point_neighbours[i_point][i_nebor]].y -
                      centroid_[1];
            tem_[2] = cloud->points[point_neighbours[i_point][i_nebor]].z -
                      centroid_[2];

            covariance_matrix(1, 1) += tem_.y() * tem_.y();
            covariance_matrix(1, 2) += tem_.y() * tem_.z();
            covariance_matrix(2, 2) += tem_.z() * tem_.z();
            tem_ *= tem_.x();
            covariance_matrix(0, 0) += tem_.x();
            covariance_matrix(0, 1) += tem_.y();
            covariance_matrix(0, 2) += tem_.z();
            covariance_matrix(1, 0) = covariance_matrix(0, 1);
            covariance_matrix(2, 0) = covariance_matrix(0, 2);
            covariance_matrix(2, 1) = covariance_matrix(1, 2);
        }
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> es;
        es.compute(covariance_matrix);
        eigen_value.row(i_point) =
            es.eigenvalues(); //升序排列，lamda0<lamda1<lamda2
        line_(i_point, 0) =
            (sqrt(eigen_value(i_point, 2)) - sqrt(eigen_value(i_point, 1))) /
            sqrt(eigen_value(i_point, 2));
        plane_(i_point, 0) =
            (sqrt(eigen_value(i_point, 1)) - sqrt(eigen_value(i_point, 0))) /
            sqrt(eigen_value(i_point, 2));
        Sphericity(i_point, 0) =
            (sqrt(eigen_value(i_point, 0))) / sqrt(eigen_value(i_point, 2));
    }
}

void find_K_nebor(int K_nebor, vector<vector<int>> &point_neighbours,
                  PointCloud<PointT>::Ptr cloud) {
    KdTreeFLANN<PointT> tree;
    tree.setInputCloud(cloud);
    int point_num = static_cast<int>(cloud->points.size());
    vector<int> pointIdxNKNSearch;
    vector<float> pointNKNSquaredDistance;
    point_neighbours.resize(cloud->points.size(), pointIdxNKNSearch);
    for (int i_points = 0; i_points < point_num; i_points++) {
        pointIdxNKNSearch.clear();
        tree.nearestKSearch(cloud->points[i_points], K_nebor, pointIdxNKNSearch,
                            pointNKNSquaredDistance);
        point_neighbours[i_points].swap(pointIdxNKNSearch);
    }
}

auto find_K_nebor1=[](int K_nebor,
                  PointCloud<PointT>::Ptr cloud) ->vector<vector<int>>{
    KdTreeFLANN<PointT> tree;
    tree.setInputCloud(cloud);
    int point_num = static_cast<int>(cloud->points.size());
    vector<int> pointIdxNKNSearch;
    vector<float> pointNKNSquaredDistance;
    vector<vector<int>> point_neighbours;
    point_neighbours.resize(cloud->points.size(), pointIdxNKNSearch);
    for (int i_points = 0; i_points < point_num; i_points++) {
        pointIdxNKNSearch.clear();
        tree.nearestKSearch(cloud->points[i_points], K_nebor, pointIdxNKNSearch,
                            pointNKNSquaredDistance);
        point_neighbours[i_points].swap(pointIdxNKNSearch);
    }
    return point_neighbours;
};



// svd求特征值
void test3() {
    PointCloudT cloud_ground;
    // io::loadPCDFile("/home/admins/桌面/github/SubstrateDevelopment/data/pointcloud.pcd",
    // *cloud);
    pcl::io::loadPLYFile("/home/admins/workspace_log8.20/workspace_2557760/"
                         "tmp_tof_data_wire.ply",
                         cloud_ground);
    // Create covariance matrix.
    // 1. calculate (x,y,z) mean
    float mean_x = 0., mean_y = 0., mean_z = 0.;
    for (size_t pt = 0u; pt < cloud_ground.points.size(); ++pt) {
        mean_x += cloud_ground.points[pt].x;
        mean_y += cloud_ground.points[pt].y;
        mean_z += cloud_ground.points[pt].z;
    }
    if (cloud_ground.points.size()) {
        mean_x /= cloud_ground.points.size();
        mean_y /= cloud_ground.points.size();
        mean_z /= cloud_ground.points.size();
    }
    // 2. calculate covariance
    // cov(x,x), cov(y,y), cov(z,z)
    // cov(x,y), cov(x,z), cov(y,z)
    float cov_xx = 0., cov_yy = 0., cov_zz = 0.;
    float cov_xy = 0., cov_xz = 0., cov_yz = 0.;
    for (int i = 0; i < cloud_ground.points.size(); i++) {
        cov_xx += (cloud_ground.points[i].x - mean_x) *
                  (cloud_ground.points[i].x - mean_x);
        cov_xy += (cloud_ground.points[i].x - mean_x) *
                  (cloud_ground.points[i].y - mean_y);
        cov_xz += (cloud_ground.points[i].x - mean_x) *
                  (cloud_ground.points[i].z - mean_z);
        cov_yy += (cloud_ground.points[i].y - mean_y) *
                  (cloud_ground.points[i].y - mean_y);
        cov_yz += (cloud_ground.points[i].y - mean_y) *
                  (cloud_ground.points[i].z - mean_z);
        cov_zz += (cloud_ground.points[i].z - mean_z) *
                  (cloud_ground.points[i].z - mean_z);
    }
    // 3. setup covariance matrix Cov
    Eigen::MatrixXf Cov(3, 3);
    Cov << cov_xx, cov_xy, cov_xz, cov_xy, cov_yy, cov_yz, cov_xz, cov_yz,
        cov_zz;
    Cov /= cloud_ground.points.size();

    // Singular Value Decomposition: SVD
    Eigen::JacobiSVD<Eigen::MatrixXf> SVD(
        Cov, Eigen::DecompositionOptions::ComputeFullU);
    // use the least singular vector as normal
    // model.normal = (SVD.matrixU().col(2));
    std::cout << "test3" << SVD.matrixU().col(2) << endl;
    std::cout << "test3" << SVD.matrixU() << endl;
    // d is directly computed substituting x with s^ which is a good
    // representative for the points belonging to the plane
    // Eigen::MatrixXf mean_seeds(3, 1);
    // mean_seeds << mean_x, mean_y, mean_z;
    // according to normal^T*[x,y,z]^T = -d
    // model.d = -(model.normal.transpose() * mean_seeds)(0, 0);

    // ROS_WARN_STREAM("Model: " << model.normal << " " << model.d);
}

//求特征值
void test1() {
    pcl::PCDReader reader;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(
        new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPLYFile("/home/admins/workspace_log8.20/workspace_2557760/"
                         "tmp_tof_data_wire.ply",
                         *cloud);

    int cld_sz = cloud->size();
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    normals->resize(cld_sz);

    //计算中心点坐标
    double center_x = 0, center_y = 0, center_z = 0;
    for (int i = 0; i < cld_sz; i++) {
        center_x += cloud->points[i].x;
        center_y += cloud->points[i].y;
        center_z += cloud->points[i].z;
    }
    center_x /= cld_sz;
    center_y /= cld_sz;
    center_z /= cld_sz;
    //计算协方差矩阵
    double xx = 0, xy = 0, xz = 0, yy = 0, yz = 0, zz = 0;
    for (int i = 0; i < cld_sz; i++) {
        xx += (cloud->points[i].x - center_x) * (cloud->points[i].x - center_x);
        xy += (cloud->points[i].x - center_x) * (cloud->points[i].y - center_y);
        xz += (cloud->points[i].x - center_x) * (cloud->points[i].z - center_z);
        yy += (cloud->points[i].y - center_y) * (cloud->points[i].y - center_y);
        yz += (cloud->points[i].y - center_y) * (cloud->points[i].z - center_z);
        zz += (cloud->points[i].z - center_z) * (cloud->points[i].z - center_z);
    }
    //大小为3*3的协方差矩阵
    Eigen::Matrix3f covMat(3, 3);
    covMat(0, 0) = xx / cld_sz;
    covMat(0, 1) = covMat(1, 0) = xy / cld_sz;
    covMat(0, 2) = covMat(2, 0) = xz / cld_sz;
    covMat(1, 1) = yy / cld_sz;
    covMat(1, 2) = covMat(2, 1) = yz / cld_sz;
    covMat(2, 2) = zz / cld_sz;

    //求特征值与特征向量
    Eigen::EigenSolver<Eigen::Matrix3f> es(covMat);
    Eigen::Matrix3f val = es.pseudoEigenvalueMatrix();
    Eigen::Matrix3f vec = es.pseudoEigenvectors();

    std::cout << "val" << val << endl;
    std::cout << "vec" << vec << endl;
    //找到最小特征值t1
    double t1 = val(0, 0);
    int ii = 0;
    if (t1 > val(1, 1)) {
        ii = 1;
        t1 = val(1, 1);
    }
    if (t1 > val(2, 2)) {
        ii = 2;
        t1 = val(2, 2);
    }

    //最小特征值对应的特征向量v_n
    Eigen::Vector3f v(vec(0, ii), vec(1, ii), vec(2, ii));
    std::cout << "法向量：" << v << endl;
    //特征向量单位化
    v /= v.norm();
    std::cout << "法向量：" << v.transpose() << endl;
    for (int i = 0; i < cld_sz; i++) {
        normals->points[i].normal_x = v(0);
        normals->points[i].normal_y = v(1);
        normals->points[i].normal_z = v(2);
        normals->points[i].curvature = t1 / (val(0, 0) + val(1, 1) + val(2, 2));
    }
    cin.get();
}

//求点领域内的法向量
void test2() {
    PointCloudT::Ptr cloud(new PointCloudT);
    // io::loadPCDFile("/home/admins/桌面/github/SubstrateDevelopment/data/pointcloud.pcd",
    // *cloud);
    pcl::io::loadPLYFile("/home/admins/workspace_log8.20/workspace_2557760/"
                         "tmp_tof_data_wire.ply",
                         *cloud);
    //         *cloud
    //点云特征计算********************************************************
    int K_nebor = 10;
    vector<vector<int>> point_neighbours,point_neighbours11;
    find_K_nebor(K_nebor, point_neighbours, cloud);
    point_neighbours11=find_K_nebor1(K_nebor,cloud);
    MatrixXf eigen_value, line_, plane_, Sphericity;
    eigen_value_(cloud, point_neighbours, K_nebor, eigen_value, line_, plane_,
                 Sphericity);
    std::cout << "lamda0" << eigen_value(1,2) << endl;
    eigen_value_(cloud, point_neighbours11, K_nebor, eigen_value, line_, plane_,
                 Sphericity);            
    std::cout << "lamda0" <<  eigen_value(1,2) << endl;
    
}

//点云读取显示
int test4() {

    PointCloudT::Ptr cloud(new PointCloudT);

    // 读取点云
    if (pcl::io::loadPLYFile("/home/admins/workspace_log8.20/workspace_2557760/"
                             "tmp_tof_data_wire.ply",
                             *cloud) < 0) {
        std::cout << "error";
    }
    // 点云显示
    pcl::visualization::PCLVisualizer::Ptr viewer(
        new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    viewer->setPointCloudRenderingProperties(
        pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    viewer->initCameraParameters();
    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }
}

//eigen 线性求解
int test5()
{
   Matrix3f A;
   Vector3f b,b0;
   A << 1,2,3,  4,5,6,  7,8,10;
   b << 3, 3, 4;
   b0<< 0, 0, 0;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the vector b:\n" << b << endl;
   Vector3f x = A.colPivHouseholderQr().solve(b);
   Vector3f x0 = A.colPivHouseholderQr().solve(b0);
   cout << "The solution is:\n" << x << endl;
   cout << "The solution is:\n" << x0 << endl;

     //求特征值与特征向量
    Eigen::EigenSolver<Eigen::Matrix3f> es(A);
    Eigen::Matrix3f val = es.pseudoEigenvalueMatrix();
    Eigen::Matrix3f vec = es.pseudoEigenvectors();

    std::cout << "val" << val << endl;
    std::cout << "vec" << vec << endl;
}


int main() {
    // test1();
    test2();
    return 0;
}
