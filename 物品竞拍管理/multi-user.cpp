//
//  multi-user.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 20/4/2021.
//

#include "multi-user.hpp"
using string = std::string;

bool UserList::add_user(std::string username){
    if(!search_user(username)){
        this->user_list.push_back(username);
        return true;
    }
    else{
        std::cout << GetLocalTime() << "用户[" << username << "]已存在" << std::endl;
        return false;
    }
}

bool UserList::search_user(std::string username){
    if(this->user_list.empty()){
        return false;
    } // 用户列表为空直接返回false
    else{
        for(auto iter = this->user_list.begin(); iter != this->user_list.end(); iter++){
            if(username.compare(*iter) == 0){
                std::cout << GetLocalTime() << "已找到名为 [" << *iter << "] 的用户" << std::endl;
                return true;
            } // compare函数返回值为0时字符串匹配成功
        }
        return false;
    }
}

UserList::UserList(void){
    std::cout << GetLocalTime() << "已创建用户列表对象" << std::endl;
    this->add_user("田所浩二"); // Debug用 正式发布要删掉
}

UserList::~UserList(void){
    
}

bool UserLogin(string username, string token, UserList* default_userlist){
    if(isUserExisting(username, default_userlist)){
        return true;
    }
    else{
        return false;
    }
}

bool isUserExisting(string username, UserList* default_userlist){
    return default_userlist->search_user(username);
}
