//
//  Data_Reader.h
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/8/24.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//
//该类的功能为：从存储数据的文件中读取相应的数据

#ifndef ML_Algorithm_Data_Reader_h
#define ML_Algorithm_Data_Reader_h
#include <vector>
#include <utility>
#include <string>
#endif

using namespace std;

class Data_Reader{
private:
    string file_address;//数据文件的地址

public:
    //重载构造函数
    Data_Reader(string file_address);
    //参数file_address表示存储数据文件的地址
    
    //从atff格式的文件中读取数据
    pair< vector< vector<float> >, vector<string> > Read_from_arff();
    //输出参数的第一项表示所存储的数据，第二项表示数据所对应的类标签。如果数据没有对应的类标签，则该容器为空
};