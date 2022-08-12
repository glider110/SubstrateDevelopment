/*
 * @Author: glider
 * @Date: 2022-08-11 09:50:02
 * @LastEditTime: 2022-08-11 09:59:56
 * @FilePath: /SubstrateDevelopment/modules/ImageUndistort/undistort2_2.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */
//
// Created by jiang on 2020/4/29.
//
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    const cv::Mat K = ( cv::Mat_<double> ( 3,3 ) << 931.73, 0.0, 480.0, 0.0, 933.16, 302.0, 0.0, 0.0, 1.0 );
    const cv::Mat D = ( cv::Mat_<double> ( 5,1 ) << -1.7165e-1, 1.968259e-1, 0.0, 0.0, -3.639514e-1 );

    const string str = "/home/admins/桌面/github/SubstrateDevelopment/modules/ImageUndistort/data/";
    const int nImage = 5;
    const int ImgWidth = 960;
    const int ImgHeight = 640;

    cv::Mat map1, map2;
    cv::Size imageSize(ImgWidth, ImgHeight);
    const double alpha = 1;
    cv::Mat NewCameraMatrix = getOptimalNewCameraMatrix(K, D, imageSize, alpha, imageSize, 0);

    for(int i=0; i<nImage; i++)
    {
        string InputPath = str + to_string(i) + ".png";
        cv::Mat RawImage = cv::imread(InputPath);
        cv::imshow("RawImage", RawImage);

        cv::Mat UndistortImage;
//        cv::undistort(RawImage, UndistortImage, K, D, K);
        cv::undistort(RawImage, UndistortImage, K, D, NewCameraMatrix);
        cv::imshow("UndistortImage", UndistortImage);

        string OutputPath = str + to_string(i) + "_un2" + ".png";
        cv::imwrite(OutputPath, UndistortImage);
        cv::waitKey(0);
    }

    return 0;
}

