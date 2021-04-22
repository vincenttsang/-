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
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>

typedef unsigned int item_condition_num;
typedef bool flag;

class Item{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & item_name;
        ar & item_owner;
        ar & item_uuid;
        ar & item_condition_in_number;
        ar & item_condition;
        ar & item_introduction;
    }

public:
    void set_item_name(std::string name_from_input);
    void set_item_owner(std::string owner_from_input);
    void set_item_uuid(std::string uuid_from_input);
    void set_item_condition_in_number(item_condition_num num_from_input);
    void set_item_condition(std::string condition_from_input);
    void set_item_introduction(std::string introduction_from_input);
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
void SaveItemToDisk(Item &item, std::string filename);
void ReadItemFromDisk(std::string filename, Item &item);

#endif /* item_hpp */
