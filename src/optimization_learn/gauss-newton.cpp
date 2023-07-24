/*
 * @Author: glider
 * @Date: 2023-07-16 10:18:02
 * @LastEditTime: 2023-07-16 10:25:14
 * @FilePath: /SubstrateDevelopment/src/optimization_learn/gauss-newton.cpp
 * @Version:  v0.01
 * @Description: https://www.cnblogs.com/penuel/p/12941607.html
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>
#include<stdlib.h>

using namespace std;
using namespace Eigen;


int main(int argc, char **argv) {
    double ar = 1.0, br = 2.0, cr = 1.0;    //真实参考值
    double ae = 20.0, be = -10.0, ce = 10.0; //初始值，不能太大，初始化很重要

    int N = 100;   //数据总点数

    double w_sigma = 1.0;  //噪声sigma值
    double inv_sigma = 1.0 / w_sigma;

    cv::RNG rng;   // opencv随机数产生

    vector<double> x_data, y_data;  //数据，生成真值数据加上随机数模拟实际采样值
    for(int i=0; i<N; i++){
        double x = i / 100.0;
        x_data.push_back(x);
        y_data.push_back( exp(ar*x*x + br*x + cr) + rng.gaussian(w_sigma*w_sigma) );

    }

    int iterations = 100;  //迭代次数
    double cost = 0, lastCost= 0;  //每次迭代的误差平方和，用于判断退出迭代次数

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for ( int iter=0; iter<iterations; iter++ ){
        Matrix3d H = Matrix3d::Zero();
        Vector3d b = Vector3d::Zero();
        cost = 0;

        for(int i=0; i<N; i++){
            double xi = x_data[i], yi = y_data[i];
            double error = yi - exp( ae*xi*xi + be*xi + ce );  
            Vector3d J;   //雅克比矩阵
            J[0] = -xi * xi * exp(ae * xi * xi + be * xi + ce);  // de/da
            J[1] = -xi * exp(ae * xi * xi + be * xi + ce);  // de/db
            J[2] = -exp(ae * xi * xi + be * xi + ce);  // de/dc

            H += inv_sigma * inv_sigma * J * J.transpose();
            b += -inv_sigma * inv_sigma * error * J;

            cost += error * error;
        }

        //求解线性方程  Hx = b
        Vector3d dx = H.ldlt().solve(b);
        if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost >= lastCost) {   //误差变大，找到最小值，退出迭代
            cout << "cost: " << cost << ">= last cost: " << lastCost << ", break." << endl;
            break;
        }

        ae += dx[0];
        be += dx[1];
        ce += dx[2];

        lastCost = cost;

        cout << "total cost: " << cost << ", \t\tupdate: " << dx.transpose() <<
             "\t\testimated params: " << ae << "," << be << "," << ce << endl;
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;

    cout << "estimated abc = " << ae << ", " << be << ", " << ce << endl;
    return 0;
}

