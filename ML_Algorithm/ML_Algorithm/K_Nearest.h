//
//  K_Nearest.h
//  ML_Algorithm
//
//  Created by John_RealMadrid on 16/2/27.
//  Copyright © 2016年 John_RealMadrid. All rights reserved.
//  在当前的代码中，只有对kd树的搜索过程，并没有对目标数据类标签的决策过程

#ifndef K_Nearest_h
#define K_Nearest_h

#include <iostream>
#include <vector>

using namespace std;

class K_Nearest;

//定义kd树的结点
class kd_tree_node{
private:
    vector<double> data; // 表示该结点所存储的数据
    string data_class; // 表示该结点数据的类标签
    int split; // 表示在该结点处是用第几维的数据进行的分割
    kd_tree_node* right {nullptr}; // 表示右子结点
    kd_tree_node* left {nullptr}; // 表示左子结点
public:
    friend class K_Nearest;
};

//定义k近邻算法的类
class K_Nearest{
private:
    kd_tree_node* kd_tree; // 表示kd树的根结点
    vector<vector<double>> train_data; // 表示训练数据
    vector<string> train_data_class; // 表示训练数据的类标签
    int data_dimension; // 表示训练数据的维度
    
    vector<double> find_nearest_data(kd_tree_node*, vector<double>);
    void create_kd_tree(kd_tree_node*, vector<vector<double>>, int);
    double calculate_distance(vector<double>, vector<double>);
public:
    K_Nearest(vector<vector<double>>, int);
    vector<vector<double>> find_k_nearest_data(vector<double>, int K = 1);
};

#endif /* K_Nearest_h */
