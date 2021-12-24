#include "SkidDetection.h"

void NS_SKIDDETECTION::SkidDetection::init(/* args */)
{
    load_img();
    load_pose();
    
}


void NS_SKIDDETECTION::SkidDetection::detect_skid()
{
    // cout <<"xxxx:"<< m_fusion_position[1].timestamp<< endl;
    // cout <<"xxxx:"<< m_fusion_position[1].pose.x << endl;
    // cout <<"xxxx:"<< m_fusion_position[1].pose.y << endl;
    // cout <<"xxxx:"<< m_fusion_position[1].pose.yaw << endl;
    // cout <<"m_fusion_position size:"<<m_fusion_position.size()<< endl;
    // cout <<"m_origin_img size:"<<m_origin_img.size()<< endl;

    int pre_pose_index=0;
    for (size_t i = 0; i < m_origin_img.size()-1; i++)
    {
        for (size_t j = 0; j < m_fusion_position.size(); j++)
        {           
            if (abs(m_origin_img[i].timestamp-m_fusion_position[j].timestamp)<0.1)
            {
                
                Mat flow;
                calcOpticalFlowFarneback(m_origin_img[i].imag, m_origin_img[i+1].imag, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
                cout << flow.size() << endl;  //对原图像每个像素都计算光流
                float sum_distance=0;
                int num_count=0;
                for (size_t y = 0;y < m_origin_img[i].imag.rows; y += 20)
                {
                    for (size_t x=0; x < m_origin_img[i].imag.cols; x += 20)
                    {
                        Point2f fxy = flow.at<Point2f>(y, x);
                        float distance=sqrt(fxy.x*fxy.x+fxy.y*fxy.y);
                        sum_distance += distance;
                        num_count++;
                        if (distance > 2)
                        {
                            line(m_origin_img[i].imag, Point(x,y), Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), CV_RGB(255, 0, 0), 1, 8);
                        }
                    }
                }
                cout <<"imag :"<< i <<"    时间戳:" << m_origin_img[i].timestamp << endl;
                cout <<"pose :"<< j <<"    时间戳:" << m_fusion_position[j].timestamp << endl;
                float poseX = abs(m_fusion_position[j].pose.x-m_fusion_position[pre_pose_index].pose.x);
                float poseY = abs(m_fusion_position[j].pose.y-m_fusion_position[pre_pose_index].pose.y);
                float poseYAW = abs(m_fusion_position[j].pose.yaw-m_fusion_position[pre_pose_index].pose.yaw);
                pre_pose_index=j;
                float space_distance=sqrt(poseX*poseX+poseY*poseY);
                float light_distance=sum_distance/num_count;
                cout <<"pose diff X:" << poseX << endl;
                cout <<"pose diff Y:"<< poseY << endl;
                cout <<"pose diff YAW:" << poseYAW << endl;
                cout <<"optical distance: "<< light_distance << endl;
                cout <<" pose  distance: "<< space_distance << endl;
                //逻辑判定（光流+融合姿态）
                if (light_distance < 0.5 && space_distance > 10)
                {
                    cout <<"============>>>>打滑...."   << endl;
                }
                else if (light_distance < 0.5 && space_distance < 5)
                {
                    cout << "============>>>>静止...."   << endl; 
                }
                else if ((light_distance > 2 && space_distance < 2) ||poseYAW > 1)
                {
                    cout << "============>>>>旋转...."   << endl; 
                }
                else
                {
                    cout << "============>>>>正常...."   << endl; 
                }
                //复制原来的图片
                imshow("稠密光流：", m_origin_img[i].imag);
                waitKey(0);
            }
            if (abs(m_origin_img[i].timestamp-m_fusion_position[j].timestamp)<0.1) break;
        }
    }
    


}
    

void NS_SKIDDETECTION::SkidDetection::load_img()
{
    Mat img;
    cv::glob(m_folder, filenames); 
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        vector<string> v1,v;
        STR_IMG tmp;
        // cout << filenames[i] << endl;
        img = imread(filenames[i]);
        Rect roi(0, 0, 640,360); 
        tmp.imag.create(img(roi).rows, img(roi).cols, CV_8UC1);
        cvtColor(img(roi), tmp.imag, CV_RGB2GRAY); 
        SplitString(filenames[i], v1, ".jpg");
        // cout << v1[0]<< endl;
        SplitString(v1[0],  v,  "/");
        tmp.timestamp= atof(v[v.size() - 1].c_str());
        m_origin_img.push_back(tmp);
        // cout << tmp.timestamp<< endl;
    }
}   


void NS_SKIDDETECTION::SkidDetection::load_pose()
{
	ifstream inFile(m_pathPose, ios::in);
	string lineStr;
	vector<vector<string>> strArray;
    ifstream fp(m_pathPose); //定义声明一个ifstream对象，指定文件路径
    string line;
    getline(fp,line); //跳过列名，第一行不做处理
    while (getline(fp,line)){ //循环读取每行数据
        STR_POSE_  temp_pose_;
        STR_POSE     temp_pose;
        vector<float> data_line;
        string number;
        istringstream readstr(line); //string数据流化
        for(int j = 0;j < 11;j++){ 
            getline(readstr,number,','); //循环读取数据
            data_line.push_back(atof(number.c_str())); 
        }
        temp_pose_.x = data_line[1];
        temp_pose_.y = data_line[2];
        temp_pose_.yaw = data_line[3];
        temp_pose.pose = temp_pose_;
        temp_pose.timestamp = data_line[0]; 
        m_fusion_position.push_back(temp_pose);
    }

}