/*
 * @Author: glider
 * @Date: 2023-07-21 10:21:48
 * @LastEditTime: 2023-07-21 10:49:24
 * @FilePath: /SubstrateDevelopment/src/optimization_learn/convex_optimization.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <ceres/ceres.h>
#include <ceres/rotation.h>

// 代价函数
struct CostFunctor {
    CostFunctor(double observed_x, double observed_y)
        : observed_x(observed_x), observed_y(observed_y) {}

    template <typename T>
    bool operator()(const T* const pose, T* residuals) const {
        T predicted_x = pose[0] + T(2.0) * ceres::cos(pose[2]);
        T predicted_y = pose[1] + T(2.0) * ceres::sin(pose[2]);

        residuals[0] = observed_x - predicted_x;
        residuals[1] = observed_y - predicted_y;

        return true;
    }

    double observed_x;
    double observed_y;
};

int main() {
    // 初始化优化问题
    ceres::Problem problem;

    // 添加节点 - 初始位姿
    double pose[3] = {0.0, 0.0, 0.0};
    problem.AddParameterBlock(pose, 3);

    // 添加观测数据posepose
    double observed_x = 2.0;
    double observed_y = 2.0;
    ceres::CostFunction* cost_function =
        new ceres::AutoDiffCostFunction<CostFunctor, 2, 3>(
            new CostFunctor(observed_x, observed_y));
    problem.AddResidualBlock(cost_function, nullptr, pose);

    // 配置求解器选项
    ceres::Solver::Options options;
    options.minimizer_progress_to_stdout = true;

    // 解决优化问题
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    // 输出优化结果
    std::cout << summary.FullReport() << "\n";
    std::cout << "Final pose: \n";
    std::cout << "x: " << pose[0] << "\n";
    std::cout << "y: " << pose[1] << "\n";
    std::cout << "theta: " << pose[2] << "\n";

    return 0;
}



// #include <iostream>
// #include <ceres/ceres.h>

// // 自定义代价函数类
// struct CostFunctor {
//     CostFunctor(double observed_x, double observed_y)
//         : observed_x(observed_x), observed_y(observed_y) {}

//     template <typename T>
//     bool operator()(const T* const x, const T* const y, T* residuals) const {
//         residuals[0] = observed_x - x[0];
//         residuals[1] = observed_y - y[0];

//         return true;
//     }

//     double observed_x;
//     double observed_y;
// };

// int main() {
//     // 初始化优化问题
//     ceres::Problem problem;

//     // 添加节点
//     double pose_x = 0.0;
//     double pose_y = 0.0;
//     problem.AddParameterBlock(&pose_x, 1);
//     problem.AddParameterBlock(&pose_y, 1);

//     // 添加观测数据
//     double observed_x = 1.0;
//     double observed_y = 1.0;
//     ceres::CostFunction* cost_function =
//         new ceres::AutoDiffCostFunction<CostFunctor, 2, 1, 1>(
//             new CostFunctor(observed_x, observed_y));
//     problem.AddResidualBlock(cost_function, nullptr, &pose_x, &pose_y);

//     // 配置求解器选项
//     ceres::Solver::Options options;
//     options.minimizer_progress_to_stdout = true;

//     // 解决优化问题
//     ceres::Solver::Summary summary;
//     ceres::Solve(options, &problem, &summary);

//     // 输出优化结果
//     std::cout << summary.FullReport() << "\n";
//     std::cout << "Final pose: \n";
//     std::cout << "x: " << pose_x << "\n";
//     std::cout << "y: " << pose_y << "\n";

//     return 0;
// }

