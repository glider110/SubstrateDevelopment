/*
 * @Author: glider
 * @Date: 2023-06-27 13:38:22
 * @LastEditTime: 2023-06-27 13:50:06
 * @FilePath: /SubstrateDevelopment/src/fengbingchun/test_parse_cvs.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include "funset.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "parse_csv.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/79324555



int test_parse_cvs()
{
#ifdef __linux__
	std::ifstream file("/home/admins/project/SubstrateDevelopment/data/test_csv.csv");
#else
	std::ifstream file("../../../testdata/test_csv.csv");
#endif

	std::vector<std::vector<std::string>> data;
	CSVIterator loop(file);
	for (; loop != CSVIterator(); ++loop) {
		CSVRow row = *loop;
		std::vector<std::string> tmp(row.size());
		for (int i = 0; i < row.size(); ++i) {
			tmp[i] = row[i];
		}
		data.emplace_back(tmp);
	}

	for (int i = 0; i < data.size(); ++i) {
		for (int j = 0; j < data[i].size(); ++j) {
			fprintf(stdout, "%s\t", data[i][j].c_str());
		}
		fprintf(stdout, "\n");
	}

	return 0;
}


