//
//  multi-user.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 20/4/2021.
//

#include "multi-user.hpp"
using string = std::string;

bool UserLogin(string username, string token);
bool isUserExisting(string username);

bool UserLogin(string username, string token){
    if(isUserExisting(username)){
        return true;
    }
    else{
        return false;
    }
}

bool isUserExisting(string username){
    return true;
}
