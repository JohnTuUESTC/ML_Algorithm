//
//  result_value.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/9/28.
//  Copyright © 2015年 John_RealMadrid. All rights reserved.
//

#include <iostream>
#include "result_value.hpp"

using namespace std;

//对聚类结果进行评价
void get_result_value(vector<string> data_class, vector<int> result){
    vector<int> temp_data_class(data_class.size());//将类标签数字化
    string label = data_class[0];
    int int_label = 0;
    for (vector<string>::size_type i = 0; i < data_class.size(); i++) {
        if (data_class[i] == label) {
            temp_data_class.push_back(int_label);
        }
        else{
            label = data_class[i];
            int_label++;
            temp_data_class.push_back(int_label);
        }
    }
    
    //计算聚类的正确率
    int correct_result = 0;
    for (vector<int>::size_type i = 0; i < result.size(); i++) {
        if(result[i] == temp_data_class[i]){
            correct_result++;
        }
    }
    
    cout<<"聚类算法的准确率为："<<(float)correct_result/result.size()<<endl;
}
