//
//  server.cpp
//  物品竞拍管理服务端
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include "item.hpp"
using std::string;

int main(int argc, const char * argv[]) {
    // insert code here...
    string tmp;
    GenerateUUID(tmp);
    std::cout << tmp << std::endl;
    return 0;
}

void CreateNewItem(Item *item){
    item = new Item;
}

void LoadItemFromDisk(){
    
}

void SaveItemToDisk(){
    
}
