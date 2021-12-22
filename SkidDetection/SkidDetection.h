/*
 * @Author: your name
 * @Date: 2021-12-17 10:45:19
 * @LastEditTime: 2021-12-22 14:46:27
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /SubstrateDevelopment/SkidDetection/SkidDetection.h
 */

#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include  <vector>
#include <fstream>
#include <sstream>
#include  "./tool.h"

#pragma comment(lib,"opencv_core2410.lib")
#pragma comment(lib,"opencv_highgui2410.lib")
#pragma comment(lib,"opencv_video2410d.lib")
#pragma comment(lib,"opencv_imgproc2410.lib")
#pragma comment(lib,"opencv_features2d2410.lib")

#define MAX_CORNERS 1000

using namespace std;
using namespace cv;

namespace NS_SKIDDETECTION
{
struct STR_POSE_ 
{
    float x;
    float y;
    float yaw;
};

struct STR_IMG 
{
    Mat imag;
    float timestamp;
};

struct STR_POSE 
{
    STR_POSE_  pose;
    int status;
    float timestamp;    
};


class SkidDetection 
{
private:
    vector<STR_IMG> m_origin_img;
    vector<STR_POSE> m_fusion_position;
    bool m_flag;
    cv::String m_folder = "/home/admins/slam/slam_data/frame"; 
    cv::String m_pathPose = "/home/admins/slam/pose_fusion/fusionpose_file0.csv";
    std::vector<cv::String> filenames;
    void load_img();
    void load_pose();

public:
    void init();
    void detect_skid();
};    
    
} 
