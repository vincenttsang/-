//
//  item.hpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#ifndef item_hpp
#define item_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef unsigned int item_condition_num;
typedef bool flag;

class Item{
public:
    void set_item_name(std::string name_from_input);
    void set_item_owner(std::string owner_from_input);
    void set_item_uuid(std::string uuid_from_input);
    void set_item_condition_in_number(item_condition_num num_from_input);
    void set_item_condition(std::string condition_from_input);
    void set_item_introduction(std::string introduction_from_input);
    std::string show_item_uuid(void);
    void SaveToDisk(std::string filename);
    void ReadFromDisk(std::string filename);
    Item(void);
    ~Item(void);

private:
    std::string item_name; // 物品名
    std::string item_owner; // 物品主人
    std::string item_uuid; // 物品UUID
    item_condition_num item_condition_in_number; // 物品新旧程度数：10为全新，9为九成新，0为战损版，以此类推
    std::string item_condition; // 物品新旧程度说明
    std::string item_introduction; // 物品介绍
};

std::string GetLocalTime(void);

#endif /* item_hpp */
