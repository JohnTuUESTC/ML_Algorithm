//
//  NaiveBayes.h
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/9/7.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#ifndef ML_Algorithm_NaiveBayes_h
#define ML_Algorithm_NaiveBayes_h

#include <vector>
#include <string>
#include <map>

using namespace std;

//定义朴素贝叶斯算法的类
class NaiveBayes{
private:
    map<string, int> class_num;//存储不同类别的数目
    vector<string> test_data_class;//存储预测测试数据的分类结果
    map< pair< pair<int, string>, string >, int > feature_num;//存储不同的特征的个数
    map< int, int > feature_result_num;//存储特征不同取值的个数
    map< pair< pair<int, string>, string >, double > feature_possibility;//存储条件概率的值
    
    //计算类别个数
    void calculate_class_num(vector<string>);
    
    //计算不同特征的个数
    void calculate_feature_num(vector< vector<string> >, vector<string>);
    
    //计算特征不同取值的个数
    void calculate_feature_result_num(vector< vector<string> >);
    
    //计算条件概率的值
    void calculate_feature_possibility(int);
    
    //预测测试数据的类别
    void predict_test_data_class(vector< vector<string> >);
    
public:
    //定义类的构造函数
    NaiveBayes(vector< vector<string> >, vector<string>, vector< vector<string> >, int lambda = 1);
    
    //定义具体算法流程的函数
    void naivebayes(vector< vector<string> >, vector<string>, vector< vector<string> >, int lambda = 1);
    
    //返回算法的预测结果
    vector<string> return_data_class();
};

#endif