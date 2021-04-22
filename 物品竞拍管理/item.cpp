//
//  item.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "item.hpp"

Item::Item(void){
} //构造函数

Item::~Item(void){
} //析构函数

void Item::set_item_name(std::string name_from_input){
    this->item_name = name_from_input;
}

void Item::set_item_owner(std::string owner_from_input){
    this->item_owner = owner_from_input;
}

void Item::set_item_uuid(std::string uuid_from_input){
    this->item_uuid = uuid_from_input;
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


void SaveItemToDisk(Item &item, std::string filename){
    std::ofstream outfile(filename, std::ofstream::binary);
    boost::archive::binary_oarchive ar(outfile, boost::archive::no_header);
    ar << boost::serialization::make_binary_object(&item, sizeof(item));
    outfile.close();
}

void ReadItemFromDisk(std::string filename, Item &item){
    std::ifstream file(filename, std::ifstream::binary);
    boost::archive::binary_iarchive ia(file, boost::archive::no_header);
    ia >> item;
    file.close();
}
