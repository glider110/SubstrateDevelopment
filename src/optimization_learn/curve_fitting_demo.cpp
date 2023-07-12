/*
 * @Author: glider
 * @Date: 2023-07-12 22:31:48
 * @LastEditTime: 2023-07-12 22:55:54
 * @FilePath: /SubstrateDevelopment/src/optimization_learn/curve_fitting_demo.cpp
 * @Version:  v0.01
 * @Description: 多点拟合逼近函数
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<ceres/ceres.h>
#include<stdlib.h>
using namespace std;
using namespace cv;
//using namespace ceres;


//----第1部分----: 构建代价函数结构体，abc为待优化参数，residual为残差。
struct CURVE_FITTING_COST{
	CURVE_FITTING_COST(double x, double y):x_(x),y_(y){}
	template <typename T>
	bool operator()(const T* const abc, T*residual) const{
		residual[0] = T(y_) -ceres::exp(abc[0]*T(x_)*T(x_)+abc[1]*T(x_)+abc[2]);  //ceres::exp and exp diff 结果相同
		return true;
	}
	const double x_,y_;
};


int main(int argc, char** argv)
{
    //参数初始化设置，abc初始化为0，gaussian噪声方差为1（使用OpenCV的随机数产生器）。
	double a=3,b=2,c=1;
	double w=1;
	RNG rng;
	double abc[3]={0,0,0};
	//生成待拟合曲线的数据散点，储存在Vector里，x_data，y_data。
	vector<double> x_data, y_data;
	for(int i=0;i<1000;i++)
	{
		double x = i/1000.0;
		x_data.push_back(x);
		y_data.push_back(exp(a*x*x+b*x+c)+rng.gaussian(w));
	}

    //----第2部分----: 构建寻优问题
	//反复使用AddResidualBlock方法（逐个散点，反复1000次）
	//将每个点的残差累计求和构建最小二乘优化式
	//不使用核函数，待优化参数是abc
	ceres::Problem problem;
	for(int i=0;i<1000;i++)
	{
		problem.AddResidualBlock(new ceres::AutoDiffCostFunction<CURVE_FITTING_COST,1,3>(new CURVE_FITTING_COST(x_data[i],y_data[i])), NULL, abc);
	}

	//----第3部分----: 配置并运行求解器
	ceres::Solver::Options options;
	options.linear_solver_type=ceres::DENSE_QR;
	options.minimizer_progress_to_stdout=true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);
	cout<<"a = "<< abc[0]<<endl;
	cout<<"b = "<< abc[1]<<endl;
	cout<<"c = "<< abc[2]<<endl;

	return 0;
}
