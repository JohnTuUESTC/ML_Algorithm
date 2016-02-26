//
//  result_value.hpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/9/28.
//  Copyright © 2015年 John_RealMadrid. All rights reserved.
//

#ifndef result_value_hpp
#define result_value_hpp

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

//对算法结果进行评价
//第一个参数表示从文件中读取的数据的类标签
//第二个参数表示算法所计算出来的类标签
void get_result_value(vector<string>, vector<int>);

#endif /* result_value_hpp */
