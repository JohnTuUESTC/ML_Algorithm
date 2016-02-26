//
//  main.cpp
//  ML_Algorithm
//
//  Created by John_RealMadrid on 15/8/24.
//  Copyright (c) 2015年 John_RealMadrid. All rights reserved.
//

#include <iostream>
#include "naivebayes.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<vector<string>> train_data {{"1","S"}, {"1", "M"}, {"1", "M"}, {"1", "S"}, {"1", "S"}, {"1", "S"}, {"2", "M"}, {"2", "M"}, {"2", "L"}, {"2", "L"}, {"3", "L"}, {"3", "M"}, {"3", "M"}, {"3", "L"}, {"3", "L"}};
    vector<string> trian_data_class {"-1", "-1", "1", "1", "-1", "-1", "-1", "1", "1", "1", "1", "1", "1", "1", "-1"};
    vector<vector<string>> test_data {{"1", "L"}};
    
    NaiveBayes test(train_data, trian_data_class, test_data);
    
    vector<string> test_data_class = test.return_data_class();
    
    auto p = test_data_class.begin();
    
    while (p != test_data_class.end()) {
        cout << *p << "\t";
        p++;
    }
    return 0;
}