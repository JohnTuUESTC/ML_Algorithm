//
//  Data_Reader.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/8/24.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include "Data_Reader.h"

using namespace std;

Data_Reader::Data_Reader(string file_address){
    this->file_address = file_address;
}

//从atff格式的文件中读取数据
pair<vector< vector<float> >, vector<string>> Data_Reader::Read_from_atff(){
    vector< vector<float> > data;//用于存储实验数据
    vector<string> data_class;//用于存储数据对应的类标签
    
    fstream file(file_address.c_str(), fstream::in);
    if(!file){
        cout<<"打开数据文件出错"<<endl;
        return make_pair(data, data_class);
    }
    
    string line;//用于存储数据文件每一行的内容
    int data_flag = 0;//用于判断有没有到达存储数据的位置
    int index = 0;//记录存储数据的位置
    while (getline(file, line)) {
        //判断是否到达了数据的开始位置
        if (data_flag == 0) {
            if (line.find("@DATA") != string::npos){
                data_flag = 1;
            }
        }
        //读取实验数据
        else{
            if (line.find(",") != string::npos) {
                while (line.find(",") != string::npos) {
                    string::size_type pos = line.find(",");
                    data[index].push_back((float)atof(line.substr(0, pos - 1).c_str()));
                    line.erase(0, pos);
                }
                data_class.push_back(line);
                index++;
            }
        }
    }
    
    return make_pair(data, data_class);
}