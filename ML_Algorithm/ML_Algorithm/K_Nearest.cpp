//
//  K_Nearest.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 16/2/27.
//  Copyright © 2016年 John_RealMadrid. All rights reserved.
//  

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "K_Nearest.h"

using namespace std;

K_Nearest::K_Nearest(vector<vector<double>> data, int dimension):train_data(data), data_dimension(dimension){
    if (train_data.size() == 0) {
        return;
    }
    kd_tree = new kd_tree_node();
    create_kd_tree(this->kd_tree, train_data, 0);
}

//构造kd树
//参数deep表示当前树的深度
void K_Nearest::create_kd_tree(kd_tree_node* node, vector<vector<double>> data, int deep){
    int split = deep % data_dimension + 1;
    
    //获取数据中split维数的中间值
    vector<double> split_dimension_data;
    auto p = data.begin();
    while (p != data.end()) {
        split_dimension_data.push_back((*p)[split - 1]);
        p++;
    }
    
    sort(split_dimension_data.begin(), split_dimension_data.end());
    
    int split_data = split_dimension_data[split_dimension_data.size() / 2];
    
    //创建当前结点
    p = data.begin();
    while (p != data.end()) {
        if((*p)[split - 1] == split_data){
            node->data = *p;
            node->split = split;
            data.erase(p);
            break;
        }
        p++;
    }
    
    //依据当前的分隔值对当前数据进行分割
    vector<vector<double>> right_data;
    vector<vector<double>> left_data;
    
    p = data.begin();
    while (p != data.end()) {
        if ((*p)[split - 1] > split_data) {
            right_data.push_back(*p);
        }
        else{
            left_data.push_back(*p);
        }
        p++;
    }
    
    if (left_data.size() > 0) {
        node->left = new kd_tree_node();
        create_kd_tree(node->left, left_data, deep + 1);
    }
    
    if (right_data.size() > 0) {
        node->right = new kd_tree_node();
        create_kd_tree(node->right, right_data, deep + 1);
    }
    
}

//查找与输入数据最邻近的k个数据点
vector<vector<double>> K_Nearest::find_k_nearest_data(vector<double> data, int K){
    vector<vector<double>> k_nearest_data;
    vector<vector<double>> temp_train_data(train_data);
    kd_tree_node* temp_kd_tree = this->kd_tree;
    
    //通过不断地寻找最邻近的数据点来寻找最邻近的k个数据点
    while (K > 0) {
        vector<double> nearest_data = find_nearest_data(temp_kd_tree, data);
        k_nearest_data.push_back(nearest_data);
        
        K -= 1;
        auto p = temp_train_data.begin();
        while (p != temp_train_data.end()) {
            if (*p == nearest_data) {
                temp_train_data.erase(p);
                break;
            }
            p++;
        }
        
        delete temp_kd_tree;
        temp_kd_tree = new kd_tree_node();
        create_kd_tree(temp_kd_tree, temp_train_data, 0);
    }
    
    return k_nearest_data;
}

//查找与输入数据最近邻的数据点
vector<double> K_Nearest::find_nearest_data(kd_tree_node* kd_tree, vector<double> data){
    vector<kd_tree_node*> search_path; // 存储搜索路径
    vector<double> nearest_data; // 存储最邻近的结点
    kd_tree_node* temp_kd_tree = kd_tree;
    
    //首先寻找到与目标结点最邻近的kd树中的叶子结点
    while (temp_kd_tree != nullptr) {
        search_path.push_back(temp_kd_tree);
        nearest_data = temp_kd_tree->data;
        
        if (temp_kd_tree->data[temp_kd_tree->split - 1] < data[temp_kd_tree->split - 1]) {
            temp_kd_tree = temp_kd_tree->right;
        }
        else{
            temp_kd_tree = temp_kd_tree->left;
        }
    }
    
    //计算目标结点与当前最近邻结点的距离
    double nearest_distance = calculate_distance(data, nearest_data);
    
    //根据之前的搜索路径回溯查找，判断是否还有更临近的结点
    while (search_path.size() > 0) {
        kd_tree_node* curr_node = search_path[search_path.size() - 1];
        search_path.pop_back();
        
        //判断是否需要进入子空间
        if (fabs(data[curr_node->split - 1] - curr_node->data[curr_node->split - 1]) < nearest_distance) {
            kd_tree_node* temp_node = nullptr;
            
            if (data[curr_node->split - 1] < curr_node->data[curr_node->split - 1]) {
                temp_node = curr_node->right; // 进入右子空间
            }
            else{
                temp_node = curr_node->left; // 进入左子空间
            }
            
            if ((temp_node != nullptr) && (temp_node->data != nearest_data)) {
                search_path.push_back(temp_node);
                if (calculate_distance(data, temp_node->data) < nearest_distance) {
                    nearest_distance = calculate_distance(data, temp_node->data);
                    nearest_data = temp_node->data;
                }
            }
        }
    }
    
    return nearest_data;
}

double K_Nearest::calculate_distance(vector<double> target_data, vector<double> nearest_data){
    double distance = 0;
    double temp = 0;
    
    for (vector<double>::size_type i = 0; i < target_data.size(); i++) {
        temp = pow((target_data[i] - nearest_data[i]), 2);
    }
    
    distance = sqrt(temp);
    
    return distance;
}