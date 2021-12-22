#include "SkidDetection.h"

void NS_SKIDDETECTION::SkidDetection::init(/* args */)
{
    load_img();
    load_pose();
    
}


void NS_SKIDDETECTION::SkidDetection::detect_skid()
{
    cout <<"xxxx:"<< m_fusion_position[1].timestamp<< endl;
    cout <<"xxxx:"<< m_fusion_position[1].pose.x << endl;
    cout <<"xxxx:"<< m_fusion_position[1].pose.y << endl;
    cout <<"xxxx:"<< m_fusion_position[1].pose.yaw << endl;
    //稠密光流
    while (1)
    { 
        for (size_t i = 0; i < m_origin_img.size()-1; i++)
        {
        Mat flow;
        calcOpticalFlowFarneback(m_origin_img[i].imag, m_origin_img[i+1].imag, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        cout << flow.size() << endl;  //对原图像每个像素都计算光流
        
        for (size_t y = 0;y < m_origin_img[i].imag.rows; y += 20)
        {
            for (size_t x=0; x < m_origin_img[i].imag.cols; x += 20)
            {
                Point2f fxy = flow.at<Point2f>(y, x);
                // cout<<"fxy.x:"<<abs(fxy.x)<<endl;
                // cout<<"fxy.y:"<<abs(fxy.y)<<endl;
                float distance=sqrt(fxy.x*fxy.x+fxy.y*fxy.y);
                // if (abs(fxy.x)>1||abs(fxy.y)>1)
                if (distance > 2)
                {
                    line(m_origin_img[i].imag, Point(x,y), Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), CV_RGB(255, 0, 0), 1, 8);
                }
            }
        }
        //复制原来的图片
        imshow("稠密光流：", m_origin_img[i].imag);
        waitKey(0);
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
        cout << filenames[i] << endl;
        img = imread(filenames[i]);
        Rect roi(0, 0, 640,360); 
        tmp.imag.create(img(roi).rows, img(roi).cols, CV_8UC1);
        cvtColor(img(roi), tmp.imag, CV_RGB2GRAY); 
        SplitString(filenames[i], v1, ".jpg");
        cout << v1[0]<< endl;
        SplitString(v1[0],  v,  "/");
        tmp.timestamp= atof(v[v.size() - 1].c_str());
        m_origin_img.push_back(tmp);
        cout << tmp.timestamp<< endl;
    }
}   


void NS_SKIDDETECTION::SkidDetection::load_pose()
{
    // 读文件
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
        //将一行数据按'，'分割
        for(int j = 0;j < 11;j++){ //可根据数据的实际情况取循环获取
            getline(readstr,number,','); //循环读取数据
            data_line.push_back(atof(number.c_str())); 
        }
        // cout <<"xxxx0:"<<data_line[0]<< endl;
        // cout <<"xxxx1:"<<data_line[1]<< endl;
        // cout <<"xxxx2:"<<data_line[2]<< endl;
        temp_pose_.x = data_line[1];
        temp_pose_.y = data_line[2];
        temp_pose_.yaw = data_line[3];
        temp_pose.pose = temp_pose_;
        temp_pose.timestamp = data_line[0]; 
        m_fusion_position.push_back(temp_pose);

    }
        cout <<"size:"<<m_fusion_position.size()<< endl;

}