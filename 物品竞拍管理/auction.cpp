//
//  auction.cpp
//  物品竞拍管理服务端
//
//  Created by Vincent Tsang on 7/5/2021.
//

#include "auction.hpp"
#include "item.hpp"
#include "multi-user.hpp"
#include "utilities.hpp"

using string = std::string;
using std::vector;

extern string data_in_string;
extern UserList* default_userlist;
extern vector<Item*> item_ptr_vector;

bool out_of_time = false;
unsigned long new_price = 0;

void timer(unsigned int time, bool& out_of_time){
    out_of_time = false;
    sleep(time);
    out_of_time = true;
}
