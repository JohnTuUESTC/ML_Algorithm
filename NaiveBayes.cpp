//
//  NaiveBayes.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/9/7.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "naivebayes.h"

using namespace std;

//计算类别个数
void NaiveBayes::calculate_class_num(vector<string> train_data_class){
    //在训练数据的类别中寻找不同类别的名称
    for (vector<string>::size_type i = 0; i < train_data_class.size(); i++) {
        if (class_num.count(train_data_class[i]) == 0) {
            class_num[train_data_class[i]] = 1;
        }
        else{
            class_num[train_data_class[i]] += 1;
        }
    }
}

//计算不同特征的个数
void NaiveBayes::calculate_feature_num(vector< vector<string> > train_data, vector<string> train_data_class){
    for (vector< vector<string> >::size_type i = 0; i < train_data.size(); i++) {
        for (vector<string>::size_type j = 0; j < train_data[i].size(); j++) {
            //判断特征是否已被存储
            if (feature_num.count(make_pair(make_pair((int)j, train_data[i][j]), train_data_class[(int)i])) == 0){
                feature_num[make_pair(make_pair((int)j, train_data[i][j]), train_data_class[(int)i])] = 1;
            }
            else{
                feature_num[make_pair(make_pair((int)j, train_data[i][j]), train_data_class[(int)i])] += 1;
            }
        }
    }
}

//计算特征不同取值的个数
void NaiveBayes::calculate_feature_result_num(vector< vector<string> > train_data){
    map< pair<int, string>, int > feature_results_num;//存储特征取不同值时的个数
    
    for (vector< vector<string> >::size_type i = 0; i < train_data.size(); i++) {
        for (vector<string>::size_type j = 0; j < train_data[i].size(); j++) {
            if (feature_results_num.count(make_pair((int)j, train_data[i][j])) == 0) {
                feature_results_num[make_pair((int)j, train_data[i][j])] = 1;
            }
            else{
                feature_results_num[make_pair((int)j, train_data[i][j])] += 1;
            }
        }
    }
    
    map< pair<int, string>, int >::iterator p = feature_results_num.begin();
    while (p != feature_results_num.end()) {
        if (feature_result_num.count(p->first.first) == 0) {
            feature_result_num[p->first.first] = 1;
        }
        else{
            feature_result_num[p->first.first] += 1;
        }
        p++;
    }
}

//计算条件概率的值
void NaiveBayes::calculate_feature_possibility(int lambda){
    map< pair< pair<int, string>, string>, int>::iterator p = feature_num.begin();
    while ( p != feature_num.end() ) {
        feature_possibility[p->first] = (feature_num[p->first] + (double)lambda)/(class_num[p->first.second] + feature_result_num[p->first.first.first] * (double)lambda);
        p++;
    }
}

//预测测试数据的分类
void NaiveBayes::predict_test_data_class(vector< vector<string> > test_data){
    //初始化存储测试数据类别的容器
    for (vector< vector<string> >::size_type i = 0; i < test_data.size(); i++) {
        test_data_class.push_back("");
    }
    
    int train_data_num = 0;//测试数据的数目
    map<string,int>::iterator p = class_num.begin();
    while (p != class_num.end()) {
        train_data_num += p->second;
        p++;
    }
    
    //针对每一个类别，计算其概率，选择其中最大的值作为测试数据的分类
    for (vector< vector<string> >::size_type i = 0; i < test_data.size(); i++) {
        double max_possibility = 0;//表示最大可能类别的概率
        string data_class;//表示数据的类别
        
        map<string, int>::iterator p = class_num.begin();
        while (p != class_num.end()) {
            double possibility = 1;//表示测试数据为该类别时的概率
            
            for (vector<string>::size_type j = 0; j < test_data[i].size(); j++) {
                possibility *= feature_possibility[make_pair(make_pair((int)j, test_data[i][j]), p->first)];
            }
            
            possibility *= (class_num[p->first]/(double)train_data_num);
            //判断该分类的概率是否为最大值
            if (possibility > max_possibility) {
                max_possibility = possibility;
                data_class = p->first;
            }
            p++;
        }
        
        //存储该测试用例的类别
        test_data_class[(int)i] = data_class;
    }
}

//实现算法具体流程的函数
//第一个参数表示训练数据，第二个参数表示训练数据的类别
//第三个参数表示需要进行分类的测试数据
//第四个参数表示在对概率为0时的处理，默认值为1，表示拉普拉斯平滑
void NaiveBayes::naivebayes(vector< vector<string> > train_data, vector<string> train_data_class, vector< vector<string> > test_data, int lambda){
    
    calculate_class_num(train_data_class);//计算不同类别的个数
    calculate_feature_num(train_data, train_data_class);//计算不同特征的个数
    calculate_feature_result_num(train_data);
    calculate_feature_possibility(lambda);//计算条件概率的值
    predict_test_data_class(test_data);//预测测试数据的类别
}

//实现类的构造函数
NaiveBayes::NaiveBayes(vector< vector<string> > train_data, vector<string> train_data_class, vector< vector<string> > test_data, int lambda){
    naivebayes(train_data, train_data_class, test_data, lambda);
}

vector<string> NaiveBayes::return_data_class(){
    return test_data_class;
}
