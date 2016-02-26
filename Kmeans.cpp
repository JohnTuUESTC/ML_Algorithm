//
//  Kmeans.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/8/22.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <math.h>
#include "Kmeans.h"

using namespace std;
extern "C"

//获取样本数据的维度
void Kmeans::get_data_dimension(vector< vector<float> > data){
    vector<float> vec = data[0];
    data_dimension = vec.size();
}

//获取样本数据每一维度的范围
void Kmeans::get_data_range(vector< vector<float> > data, float (*data_range)[2]){
    //初始化存储范围的数组
    for(int i = 0; i < data_dimension; i++){
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                //存储范围的下界
                data_range[i][j]=100000;
            }
            else{
                //存储范围的上界
                data_range[i][j]=-100000;
            }
        }
    }
    
    //获取数据的范围
    for(vector< vector<float> >::size_type i = 0 ;i < data.size() ;i++){
        for(vector<float>::size_type j = 0 ;j < data[i].size() ;j++){
            if (data[i][j] < data_range[(int)j][0]) {
                data_range[(int)j][0] = data[i][j];
            }
            if (data[i][j] > data_range[(int)j][1]) {
                data_range[(int)j][1] = data[i][j];
            }
        }
    }
}

//初始化聚类中心
void Kmeans::init_k_center(float (*data_range)[2], vector< vector<float> > &k_center, int k){
    for (int i = 0; i < k; i++) {
        for (vector<float>:: size_type j = 0; j < data_dimension; j++) {
            
            //产生随机的中心点
            srand((unsigned)time(0));
            k_center[i].push_back(rand()%(int)(data_range[(int)j][1] - data_range[(int)j][0]) + data_range[(int)j][0]);
        }
    }
}

//计算数据点与聚类中心的距离
float Kmeans::calculate_distance(vector<float> data, vector<float> center){
    float distance = 0;
    
    vector<float>::iterator p1 = data.begin();
    vector<float>::iterator p2 = center.begin();
    while ((p1 != data.end()) && (p2 != center.end())) {
        float temp_distance = powf((*p1 - *p2), (float)2.0);
        distance += temp_distance;
        p1++;
        p2++;
    }
    
    return sqrtf(distance);
}

//计算每一个样本所属的类别，以及总距离
float Kmeans::calculate_data_class(vector< vector<float> > data, vector< vector<float> > k_center, vector<int> &data_class){
    float total_distance = 0;//存储数据点到聚类中心点的总距离
    float min_distance;//存储数据点到中心的最小距离
    int class_index;//存储数据点的分类
    
    for (vector< vector<float> >::size_type i = 0; i < data.size(); i++) {
        min_distance = 100000;
        class_index = 0;
        for (vector< vector<float> >::size_type j = 0; j < k_center.size(); j++) {
            float distance = calculate_distance(data[i], k_center[j]);
            if (distance < min_distance) {
                min_distance = distance;
                class_index = (int)j;
            }
        }
        total_distance += min_distance;
        data_class[(int)i] = class_index;
    }
    
    return total_distance;
}

//重新计算聚类中心
void Kmeans::calculate_new_class(vector< vector<float> > data, vector< vector<float> > &new_k_center, vector<int> data_class){
    int type_num;//一个类别所包含的数据的个数
    vector<float> new_center;//新聚类中心的坐标
    
    for (vector< vector<float> >::size_type i = 0; i < new_k_center.size(); i++) {
        type_num = 0;
        new_center.assign(new_k_center.size(), 0);
        for (vector<int>::size_type j = 0; j < data_class.size(); j++) {
            if (data_class[j] == i) {
                type_num++;
                for (int k = 0; k < data_dimension; k++) {
                    new_center[k] += data[j][k];
                }
            }
        }
        
        for (vector<float>::size_type j = 0; j < data_dimension; j++) {
            new_center[j] /= type_num;
        }
        
        new_k_center[i]=new_center;
    }
}

//普通版本Kmeans算法的实现
vector<int> Kmeans::kmeans(vector< vector<float> > data, int k, float epsilon){
    cout<<"--------------普通版本Kmeans算法开始---------------"<<endl;
    
    //获取样本数据的维度
    get_data_dimension(data);
    
    //获取数据每一维度的范围
    float (*data_range)[2] =new float[data_dimension][2];
    get_data_range(data, data_range);
    
    //初始化聚类中心
    vector< vector<float> > k_center(k);//表示k个聚类中心
    init_k_center(data_range, k_center, k);
    
    //计算每一个样本所属分类
    vector<int> data_class(data.size(), 0);
    float total_distance=calculate_data_class(data, k_center, data_class);
    cout<<"-------------------第1次迭代---------------------"<<endl;
    cout<<"总距离："<<total_distance<<endl;
    
    //开始算法的迭代
    int loop = 2;
    while (true) {
        //重新计算聚类中心
        vector< vector<float> > new_k_center(k);
        calculate_new_class(data, new_k_center, data_class);
        
        //计算新的分类以及新的目标函数值
        vector<int> new_data_class(data.size(),0);
        float new_total_distance = calculate_data_class(data, new_k_center, new_data_class);
        
        cout<<"---------------第"<<loop<<"次迭代----------------------"<<endl;
        cout<<"总距离："<<new_total_distance<<endl;
        
        //判断是否结束循环
        if ((total_distance - new_total_distance) < epsilon) {
            total_distance = new_total_distance;
            k_center = new_k_center;
            data_class = new_data_class;
            break;
        }
        
        //判断是否采纳新值
        if (new_total_distance < total_distance) {
            total_distance = new_total_distance;
            k_center = new_k_center;
            data_class = new_data_class;
        }
        
        loop++;
    }
    
    cout<<"--------------普通版本Kmeans算法结束---------------"<<endl;
    delete [] data_range;
    return data_class;
}

//模拟退火版本的Kmeans算法的实现
vector<int> Kmeans::kmeans(vector< vector<float> > data, int k, float K, float init_temperature, float end_temperature, float epsilon){
    cout<<"------------模拟退火版本Kmeans算法开始--------------"<<endl;
    
    //获取样本数据的维度
    get_data_dimension(data);
    
    //获取数据每一维度的范围
    float (*data_range)[2] =new float[data_dimension][2];
    get_data_range(data, data_range);
    
    //初始化聚类中心
    vector< vector<float> > k_center(k);//表示k个聚类中心
    init_k_center(data_range, k_center, k);
    
    //计算每一个样本所属分类
    vector<int> data_class(data.size(), 0);
    float total_distance=calculate_data_class(data, k_center, data_class);
    cout<<"-------------------第1次迭代---------------------"<<endl;
    cout<<"总距离："<<total_distance<<endl;
    
    //开始算法的迭代
    int loop = 2;
    while (init_temperature > end_temperature) {
        //重新计算聚类中心
        vector< vector<float> > new_k_center(k);
        calculate_new_class(data, new_k_center, data_class);
        
        //计算新的分类以及新的目标函数值
        vector<int> new_data_class(data.size(),0);
        float new_total_distance = calculate_data_class(data, new_k_center, new_data_class);
        
        cout<<"---------------第"<<loop<<"次迭代----------------------"<<endl;
        cout<<"总距离："<<new_total_distance<<endl;
        
        //判断两次迭代的值之差是否小于阈值
        if (total_distance - new_total_distance < epsilon) {
            break;
        }
        
        //模拟退火算法的主体
        //如果得到的新解较原最优解更优，则采纳新解
        if (new_total_distance - total_distance < 0) {
            total_distance = new_total_distance;
            k_center = new_k_center;
            data_class = new_data_class;
        }
        //如果不是，则以一定概率采纳新解
        else{
            srand((unsigned)time(0));
            if (rand() > (exp(-(new_total_distance - total_distance) / (K * init_temperature)))) {
                total_distance = new_total_distance;
                k_center = new_k_center;
                data_class = new_data_class;
            }
        }
        
        init_temperature *= K;//将温度逐渐降低
        loop++;
    }
    
    cout<<"------------模拟退火版本Kmeans算法结束--------------"<<endl;
    delete [] data_range;
    return data_class;
}

//实现普通版本Kmeans算法的构造函数
Kmeans::Kmeans(vector< vector<float> > data, int k, float epsilon){
     data_class = kmeans(data, k, epsilon);
}

//实现模拟退火版本的Kmeans算法的构造函数
Kmeans::Kmeans(vector< vector<float> > data, int k, float K, float init_temperature, float end_temperature, float epsilon){
    data_class = kmeans(data, k, k, init_temperature, end_temperature, epsilon);
}

vector<int> Kmeans::return_data_class(){
    return data_class;
}