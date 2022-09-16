/*
 * @Author: glider
 * @Date: 2021-10-12 11:30:48
 * @LastEditTime: 2022-09-16 10:45:01
 * @FilePath: /SubstrateDevelopment/example/eigen_test.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */
#ifndef M_PI
#define M_PI 3.14159265
#endif

#ifndef M_PI_2
#define M_PI_2 M_PI/2
#endif

#ifndef DEG2RAD
  #define DEG2RAD(x) ((x)*M_PI/180.0)
#endif

#ifndef RAD2DEG
  #define RAD2DEG(x) ((x)*180.0/M_PI)
#endif
#include  "iostream"
#include <Eigen/Eigen>

 using namespace std;
 using namespace Eigen;
int main(int argc, char **argv)
{
//     // Eigen/Geometry 模块提供了各种旋转和平移的表示
//     // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
//     Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    
//     // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
//     Eigen::AngleAxisd rotation_vector ( M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     //沿 Z 轴旋转 45 度
//     cout .precision(3);
//     cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;                //用matrix()转换成矩阵
//     // 也可以直接赋值
//     rotation_matrix = rotation_vector.toRotationMatrix();
//      cout<<"xxxxx\n"<<rotation_matrix<<endl;
//     // 用 AngleAxis 可以进行坐标变换
//     Eigen::Vector3d v ( 1,0,0 );
//     Eigen::Vector3d v_rotated = rotation_vector * v;
//     cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
//     // 或者用旋转矩阵
//     v_rotated = rotation_matrix * v;
//     cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

//     // 欧拉角: 可以将旋转矩阵直接转换成欧拉角
//     Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYX顺序，即roll pitch yaw顺序
//     cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

//     // 欧氏变换矩阵使用 Eigen::Isometry
//     Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
//     T.rotate ( rotation_vector );                                     // 按照rotation_vector进行旋转
//     T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // 把平移向量设成(1,3,4)
//     cout << "Transform matrix = \n" << T.matrix() <<endl;

//     // 用变换矩阵进行坐标变换
//     Eigen::Vector3d v_transformed = T*v;                              // 相当于R*v+t
//     cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

//     // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d 即可，略

//     // 四元数
//     // 可以直接把AngleAxis赋值给四元数，反之亦然
//     Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
//     cout<<"quaternion = \n"<<q.coeffs() <<endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
//     // 也可以把旋转矩阵赋给它
//     q = Eigen::Quaterniond ( rotation_matrix );
//     cout<<"quaternion = \n"<<q.coeffs() <<endl;
//     // 使用四元数旋转一个向量，使用重载的乘法即可
//     v_rotated = q*v; // 注意数学上是qvq^{-1}
//     cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;


// //   调试主方向,测试Vector3d 索引
//     Eigen::Vector3d a ;
//     a<<1,3,5;
//     cout<<"==============="<<a<<endl;
//     cout<<"==============="<<a.transpose()<<endl;
//     cout<<"==============="<<a[1]<<endl;
//     cout<<"==============="<<a.z()<<endl;


    /* 课题一:
    旋转表示方法及其相互转换 */


    /* 课题二: 不同坐标系,点的转换, slam14讲兔子坐标系*/
    //四元数
    Eigen::Quaterniond q1 = Eigen::Quaterniond(0.35, 0.2, 0.3, 0.1).normalized();
    Eigen::Quaterniond q2 = Eigen::Quaterniond(-0.5, 0.4, -0.1, 0.2).normalized();
    //平移向量
    Eigen::Vector3d t1 = Eigen::Vector3d(0.3, 0.1, 0.1);
    Eigen::Vector3d t2 = Eigen::Vector3d(-0.1, 0.5, 0.3);
    //目标向量
    Eigen::Vector3d p1 = Eigen::Vector3d(0.5, 0, 0.2);
    Eigen::Vector3d p2;
    //打印输出
    // cout << q1.coeffs() << "\n"
    // << q2.coeffs() << "\n"
    // << t1.transpose() << "\n"
    // << t2.transpose() << endl;
    //四元数求解
    p2 = q2 * q1.inverse() * (p1 - t1) + t2;
    cout << p2.transpose() << endl;
    //欧拉矩阵
    Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity();
    Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
    T1.rotate(q1.toRotationMatrix());
    T1.pretranslate(t1);
    T2.rotate(q2.toRotationMatrix());
    T2.pretranslate(t2);
    // cout << T1.matrix() << endl;
    // cout << T2.matrix() << endl;
    //欧拉矩阵求解
    // p2 = T2 * T1.inverse() * p1;
    p2 =  T1.inverse() *T2* p1;
    cout << p2.transpose() << endl;

    /* 课题三: 相同坐标变换,点的转换,闭环处理*/
    Eigen::Isometry3d T_odom_delta =Eigen::Isometry3d::Identity();
    Eigen::Isometry3d T_odom_before =Eigen::Isometry3d::Identity();
    T_odom_before.prerotate(Eigen::AngleAxisd(DEG2RAD(90),Eigen::Vector3d::UnitZ()));
    Eigen::Vector3d t_vec1 = Eigen::Vector3d(1.0, 0.0, 0.0);
    T_odom_before.pretranslate(t_vec1);
    Eigen::Isometry3d T_odom_ahead =Eigen::Isometry3d::Identity();
    T_odom_ahead.prerotate(Eigen::AngleAxisd(DEG2RAD(90),Eigen::Vector3d::UnitZ()));
    Eigen::Vector3d t_vec2 = Eigen::Vector3d(0.0, 1, 0.0);
    T_odom_ahead.pretranslate(t_vec2);
    T_odom_delta = T_odom_ahead*T_odom_before.inverse();

    Eigen::Vector3d point1 = Eigen::Vector3d(1, 0, 0);
    Eigen::Vector3d point1_trans = T_odom_before*point1;
    cout << "T_odom_delta.translate()\n"<<RAD2DEG(T_odom_delta.rotation().eulerAngles(2,1,0))<<endl;
    cout << "T_odom_delta.rotate()\n"<<T_odom_delta.translation()<<endl;
    cout << "point1_trans\n"<<point1_trans<<endl;
    
    return 0;
}





