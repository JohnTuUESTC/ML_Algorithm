//
//  Kmeans.h
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/8/22.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#ifndef ML_Algorithm_Kmeans_h
#define ML_Algorithm_Kmeans_h
#include <vector>
#include <map>
#endif

using namespace std;

//定义Kmeans算法的实现类
class Kmeans{
private:
    vector<float>::size_type data_dimension;//记录训练数据的维度
    
    //获取训练数据的维度
    void get_data_dimension(vector< vector<float> > data);
    
    //获取数据每一维度的范围
    void get_data_range(vector< vector<float> > data, float (*data_range)[2]);
    //参数dimension表示数据的维度
    
    //初始化聚类中心
    void init_k_center(float (*data_range)[2], vector< vector<float> > &k_center, int k);
    
    //计算数据点与中心点之间的距离
    float calculate_distance(vector<float> data, vector<float> center);
    
    //计算每一个样本所属类别，同时返回总距离即目标函数值
    float calculate_data_class(vector< vector<float> > data, vector< vector<float> > k_center, vector<int> &data_class);
    
    void calculate_new_class(vector< vector<float> > data, vector< vector<float> > &k_center, vector<int> data_class);
    
    //实现普通版本的kmeans算法的函数
    vector<int> kmeans(vector< vector<float> > data, int k, float epsilon);
    
    //实现模拟退火版本的Kmeans算法的函数
    vector<int> kmeans(vector< vector<float> > data, int k, float K, float init_temperature, float end_temperature, float epsilon);
    
    //对聚类结果进行评价
    void get_result_value(vector<string> data_class, vector<int> result);
public:
    //实现普通版本的Kmeans算法的初始化函数
    Kmeans(vector< vector<float> > data, vector<string> data_class, int k, float epsilon);
    //输入参数data用于存储算法的数据
    //data_class表示数据的类别
    //输入参数k表示聚类中心的个数
    //输入参数epsilon表示算法的终止条件
    
    //实现模拟退火版本的Kmeans算法的初始化函数
    Kmeans(vector< vector<float> > data, vector<string> data_class, int k, float K, float init_temperature, float end_temperature, float epsilon);
    //参数K表示玻尔兹曼常数
    //参数init_temperature表示模拟退火算法的初始温度
    //参数end_temperature表示模拟退火算法的最低温度
};