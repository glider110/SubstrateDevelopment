#include <iostream>
#include <map>
#include  "iostream"
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>

 using namespace std;
 using namespace Eigen;
  using namespace cv;
int main(int argc, char **argv)
{
    //eigen
      Matrix2d cx; cx<<3,5,1,6;
      Eigen::Vector4i vec1; vec1<<1,3,4,6,6;
     
    //opencv
    Mat aa = Mat(3, 3, CV_8U,Scalar(2));
    Mat_<int> d_ = (Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 44, 66, 34, 56);
    Matx22d bx(3,5,1,6);
    Vec2f vec;vec<<1,3,4;
   
    Mat_<int> bb=(Mat_<int>(3, 3) <<1,2,4,5,1,3);
    cout <<int(aa.at<uchar>(1, 0) )<< endl;
    cout << d_[1][0 ]<< endl;
    cout << bx(1, 1) << endl;
    cout << cx(1, 1) << endl;
    //vecter

    // map
    std::map<char, int> mymap;
    std::map<char, int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find('d');
    if (it != mymap.end()) {
        std::cout << "a => " << '\n';
        mymap.erase(it);
    }
    // print content:
    // std::cout << "elements in mymap:" <<*it<< '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';
    std::cout << "b => " << mymap.find('b')->second << '\n';
    std::cout << "e => " << mymap.find('e')->second << '\n';

}       
