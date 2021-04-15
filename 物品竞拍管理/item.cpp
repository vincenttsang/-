//
//  item.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "item.hpp"
#include <iostream>
Item::Item(void){
    completion_flag = new bool[5];
    for(int i = 0; i < 5; i++){
        completion_flag[i] = false;
    }
} //构造函数
Item::~Item(void){
    std::cout << "Fuck\n";
} //析构函数
void Item::set_item_name(std::string name_from_input){
    this->item_name = name_from_input;
}

void Item::set_item_uuid(std::string uuid_from_input){
    this->item_name = uuid_from_input;
}

void Item::set_item_condition_in_number(item_condition_num num_from_input){
    this->item_condition_in_number = num_from_input;
}

void Item::set_item_condition(std::string condition_from_input){
    this->item_condition = condition_from_input;
}

void Item::set_item_introduction(std::string introduction_from_input){
    this->item_introduction = introduction_from_input;
}
