/*
 * @Author: glider
 * @Date: 2023-07-12 21:36:42
 * @LastEditTime: 2023-07-12 22:56:17
 * @FilePath: /SubstrateDevelopment/src/optimization_learn/ceres_demo.cpp
 * @Version:  v0.01
 * @Description: ceres求极值
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include<iostream>
#include<ceres/ceres.h>
using namespace std;
//using namespace ceres;


//----第1部分----: 构建代价函数，重载（）符号
struct CostFunctor{
	template <typename T>
	bool operator()(const T* const x, T*residual) const{  //???
		// residual[0] = T(10.0)-x[0];
		residual[0] = 0.5 * pow((T(10.0)-x[0]), 2);  // 这样写是对的，0.5变成1/2就不对。
		return true;
	}
};


int main(int argc, char** argv)
{
	// 寻优参数x的初始值
	double initial_x = -3.0;
	double x = initial_x;
    //----第2部分----: 构建寻优问题
	ceres::Problem problem;
	ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CostFunctor,1,1>(new CostFunctor);
    //使用自动求导，将之前的代价函数结构体传入，第一个1是输出维度，即残差的维度，第二个1是输入维度，即待寻优参数x的维度。 
	problem.AddResidualBlock(cost_function, NULL, &x); //向问题中添加误差项，本问题比较简单，添加一个就行。
	//----第3部分----: 配置并运行求解器
    ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_QR; //配置增量方程的解法
	options.minimizer_progress_to_stdout=true;
    //输出到cout, 输出这些信息:iter cost cost_change |gradient| |step| tr_ratio tr_radius ls_iter iter_time total_time

	ceres::Solver::Summary summary;//优化信息
	ceres::Solve(options, &problem, &summary); //求解!!!,求解完成后，输入x会更新
	cout<<"out: "<<summary.BriefReport()<<endl;//输出优化的简要信息
	cout<<"x: "<<initial_x<<" -> "<<x<<endl;
	return 0;
}
