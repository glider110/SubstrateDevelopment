/*
 * @Author: glider
 * @Date: 2023-06-27 12:59:32
 * @LastEditTime: 2023-06-27 13:13:48
 * @FilePath: /SubstrateDevelopment/utils/csv.hpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
// 统计一行元素个数
namespace NS_COMMON
{
using namespace std;
int getLong(string line);
vector<vector<double>> csvRead(string filename);
bool csvWrite(vector<vector<double>> data, string output_filename);

int getLong(string line) {
    int numsize = 0;
    for (auto a : line)
        if (a == ',') numsize++;
    return numsize + 1;
}
// 主函数入口
vector<vector<double>> csvRead(string filename)
{
	vector<vector<double>> result;
	ifstream infile(filename, ios::in);
	string line;
	getline(infile, line);
	int sizex = getLong(line);
	while (getline(infile, line)) {
		stringstream ss(line);
		string str;
		vector<double> lineReader;
		for (int i = 0; i < sizex; i++) {
			getline(ss, str, ',');
			lineReader.push_back(stod(str));
		}
		result.push_back(lineReader);
	}
	return result;
}

bool csvWrite(vector<vector<double>> data, string output_filename)
{
	ofstream outFile(output_filename, ios::out);
    if (!outFile)
    {
        // out part
        cout << "打开文件失败！" << endl;

        return false;
    }
    for (auto i : data) {
        for (auto j : i) {
            outFile << j << ",";
        }
        outFile << endl;
    }
    outFile.close();
	return true;
}





} // namespace NS_COMMON