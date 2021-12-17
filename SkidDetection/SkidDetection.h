/*
 * @Author: your name
 * @Date: 2021-12-17 10:45:19
 * @LastEditTime: 2021-12-17 11:22:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /SubstrateDevelopment/SkidDetection/SkidDetection.h
 */

#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/highgui/highgui.hpp"
#include  <vector>

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
    struct STR_IMG
    {
        cv::Mat imag;
        float timestamp;
    };

    struct STR_POSE
    {
        int status;
        vector<int>  pose;
        float timestamp;    
    };
    

    class SkidDetection
    {
    private:
        STR_IMG m_origin_img;
        STR_POSE m_fusion_position;
        bool m_flag;

    public:
        void init();
        void detect_skid();
    };
    

    
    
} 
