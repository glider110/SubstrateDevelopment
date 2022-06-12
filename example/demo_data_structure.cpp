#include "iostream"
#include <Eigen/Eigen>
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include <vector>
#include<fstream>  // 文件流
#include<sstream>

using namespace std;
using namespace Eigen;
using namespace cv;

//一二维数据结构用于：线代 图像变换 旋转变换....
void test1() {
    // eigen
    Matrix2d cx;
    cx << 3, 5, 1, 6;
    Eigen::Vector4i vec1;
    vec1 << 1, 3, 4, 6, 6;
    cout << vec1;
    // opencv
    Mat aa = Mat(3, 3, CV_8U, Scalar(2));
    Mat_<int> d_ = (Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 44, 66, 34, 56);
    Matx22d bx(3, 5, 1, 6);
    Vec2f vec;
    vec << 1, 3, 4;

    Mat_<int> bb = (Mat_<int>(3, 3) << 1, 2, 4, 5, 1, 3);
    cout << int(aa.at<uchar>(1, 0)) << endl;
    cout << d_[1][0] << endl;
    cout << bx(1, 1) << endl;
    cout << cx(1, 1) << endl;
    //矩阵运算
}

 // map
void test2() {
    std::map<char, int> mymap;
    std::map<char, int>::iterator it;
    ::map<char, int> a = {{'b',33}};
    
    ::map<char, int> b({{'b',33}});
    for(auto i : a)
    {
        cout<<i.first<<endl;
        cout<<<i.second<endl;1
    }

    

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

void test3() {
    vector<int> a = {1,2,3,4,5,6};  //2,3
    vector<vector<int>> array(2);
    for (int i = 0;  i < array.size(); i++)
    {
        array[i].resize(3);
    }


    for(int i = 0; i < array.size(); i++)
    {
        for (int j = 0; j < array[0].size();j++)
        {
            array[i][j] =a[i*3+j];
        }
    }
    // std::cout << array << std::endl;
    std::cout << "e => " << array [1][2]<< std::endl;
       //写文件
    // ofstream outFile1;
    // outFile1.open("data.csv", ios::out);
    // for (size_t i = 0; i < 2; i++)
    // {
    //     for (size_t j= 0; j < 3; j++)
    //     {
    //         outFile1<< a[(i+1)*(j+1)] ;
    //     }
    //     outFile1<<"\n";
    // }
    // outFile1.close();





    ofstream outFile1;
    outFile1.open("data2.csv", ios::out);
    cout << "Size:" << array.size() << endl;
    for (int i = 0; i <2; i++) {
        for (int j = 0; j <3; j++) {
            cout << array[i][j] << " ";
            // outFile1 <<  array[i][j] << ",";
            outFile1 <<  a[i*3+j] << ",";
        }
        cout << endl;
        outFile1<<endl;
    }
       outFile1.close();
}


void ReadDataFromCsv(std::string &filename, std::vector<std::vector<std::string> > &lines_feat) {
    std::ifstream vm_info(filename.c_str());
    std::string lines, var;
    std::vector<std::string> row;

    lines_feat.clear();

    while(!vm_info.eof()) {
        getline(vm_info, lines);
        if(lines.empty())
            break;
        std::istringstream stringin(lines);
        row.clear();

        while(std::getline(stringin, var, ',')) {
            row.push_back(var);
        }
        lines_feat.push_back(row);
    }
}

int main(int argc, char **argv) {

    // test3();
    // std::vector<std::vector<std::string> > a;
    // std::string b = "data2.csv";

    // ReadDataFromCsv(b, a);
    // for (int i = 0; i <2; i++) {
    //     for (int j = 0; j <3; j++) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    test2();
    

}
