#include "SkidDetection.h"
void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


void NS_SKIDDETECTION::SkidDetection::init(/* args */)
{
    load_img();
    load_pose();
    
}


void NS_SKIDDETECTION::SkidDetection::detect_skid()
{
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
	while (getline(inFile, lineStr))
	{
		// 打印整行字符串
		cout << lineStr << endl;
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		// 按照逗号分隔
		while (getline(ss, str, ','))
            cout <<"xxxx:"<<str << endl;
			lineArray.push_back(str);   
		strArray.push_back(lineArray);
	}
}