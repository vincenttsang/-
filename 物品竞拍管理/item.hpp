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
typedef unsigned int item_condition_num;
typedef bool flag;
void GenerateUUID(std::string &id);

class Item{
public:
    void set_item_name(std::string name_from_input);
    void set_item_uuid(std::string uuid_from_input);
    void set_item_condition_in_number(item_condition_num num_from_input);
    void set_item_condition(std::string condition_from_input);
    void set_item_introduction(std::string introduction_from_input);
    Item(void);
    ~Item(void);
    
private:
    flag* completion_flag; //完成度标记为false时该项未完成
    std::string item_name; //Flag 0,物品名
    std::string item_uuid; //Flag 1,物品UUID
    item_condition_num item_condition_in_number; //Flag 2,物品新旧程度数：10为全新，9为九成新，0为战损版，以此类推
    std::string item_condition; //Flag 3,物品新旧程度说明
    std::string item_introduction; //Flag 4,物品介绍
};
#endif /* item_hpp */
