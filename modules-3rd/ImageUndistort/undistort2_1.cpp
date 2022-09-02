/*
 * @Author: glider
 * @Date: 2022-08-11 09:50:02
 * @LastEditTime: 2022-08-11 11:06:48
 * @FilePath: /SubstrateDevelopment/modules/ImageUndistort/undistort2_1.cpp
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
using namespace cv;

int main()
{
/* 
Camera.width: 640
Camera.height: 360
Camera.fx: 362.431754305133
Camera.fy: 351.841642059333
Camera.cx: 313.476639132245
Camera.cy: 182.069620737093
Camera.k1: -0.055221329162
Camera.k2: -0.049932692436
Camera.p1: 0.000000000000
Camera.p2: 0.000000000000 
*/
    //const cv::Mat K = ( cv::Mat_<double> ( 3,3 ) << 931.73, 0.0, 480.0, 0.0, 933.16, 302.0, 0.0, 0.0, 1.0 );
    // const cv::Mat D = ( cv::Mat_<double> ( 5,1 ) << -1.7165e-1, 1.968259e-1, 0.0, 0.0, -3.639514e-1 );

    const cv::Mat K=(Mat_<double> (3,3) <<  362.431,       0,        313.47,      \
                                                                0,            351.84,   182.07,           \
                                                                0,                  0,                   1);          
    const cv::Mat D = ( cv::Mat_<double> ( 5,1 ) << -0.055221329162, -0.049932692436, 0.0, 0.0, 0.0 );
    // const cv::Mat D = ( cv::Mat_<double> ( 5,1 ) <<-0.0, -0.0, 0.0, 0.0, 0.0 );





    const string str = "/home/admins/桌面/github/SubstrateDevelopment/modules/ImageUndistort/data/";
    const int nImage = 5;
    const int ImgWidth = 640;
    const int ImgHeight = 360;

    cv::Mat map1, map2;
    cv::Size imageSize(ImgWidth, ImgHeight);
    const double alpha = 1;
    cv::Mat NewCameraMatrix = getOptimalNewCameraMatrix(K, D, imageSize, alpha, imageSize, 0);
    initUndistortRectifyMap(K, D, cv::Mat(), NewCameraMatrix, imageSize, CV_16SC2, map1, map2);

    // for(int i=0; i<nImage; i++)
    // {
    //     string InputPath = str + to_string(i) + ".png";
    //     cv::Mat RawImage = cv::imread(InputPath);
    //     cv::imshow("RawImage", RawImage);

    //     cv::Mat UndistortImage;
    //     remap(RawImage, UndistortImage, map1, map2, cv::INTER_LINEAR);
    //     cv::imshow("UndistortImage", UndistortImage);

    //     string OutputPath = str + to_string(i) + "_un_glider" + ".png";
    //     cv::imwrite(OutputPath, UndistortImage);
    //     cv::waitKey(0);
    // }



    string InputPath = str  + "5.jpg";
    cv::Mat RawImage = cv::imread(InputPath);
    cv::Mat Imgahead_downsample;
    Imgahead_downsample = RawImage(Rect(320, 180, 640, 360));
    // cv::resize(RawImage, Imgahead_downsample, cv::Size(RawImage.cols/2, RawImage.rows/2));     //320x180   gray
    cv::imshow("RawImage", Imgahead_downsample);

    cv::Mat UndistortImage;
    remap(Imgahead_downsample, UndistortImage, map1, map2, cv::INTER_LINEAR);
    cv::imshow("UndistortImage", UndistortImage);

    string OutputPath = str +  "5_un_glider" + ".png";
    cv::imwrite(OutputPath, UndistortImage);
    cv::waitKey(0);
    return 0;
}