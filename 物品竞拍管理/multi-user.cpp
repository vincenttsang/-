//
//  multi-user.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 20/4/2021.
//

#include "multi-user.hpp"
using string = std::string;

bool UserList::add_user(std::string username, std::string password){
    if(!search_user(username)){
        user new_user;
        new_user.name = username;
        new_user.password = password;
        this->user_list.push_back(new_user);
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
            if(username.compare(iter->name) == 0){
                std::cout << GetLocalTime() << "已找到名为 [" << iter->name << "] 的用户" << std::endl;
                return true;
            } // compare函数返回值为0时字符串匹配成功
        }
        return false;
    }
}

bool UserList::user_login(std::string username, std::string password){
    for(auto iter = this->user_list.begin(); iter != this->user_list.end(); iter++){
        if( (username.compare(iter->name) == 0) && (password.compare(iter->password) == 0) ){
            return true; //密码正确
        }
    }
    return false; // 密码错误
}

UserList::UserList(void){
    std::cout << GetLocalTime() << "已创建用户列表对象" << std::endl;
    this->add_user("邓佳佳", "114514"); // Debug用 正式发布要删掉
}

UserList::~UserList(void){
    
}

bool UserLogin(string username, string token, UserList* default_userlist){
    if(isUserExisting(username, default_userlist)){
        if(default_userlist->user_login(username, token)){
            std::cout << GetLocalTime() << "用户 [" << username << "] 密码正确" << std::endl;
            return true;
        }
        std::cout << GetLocalTime() << "用户 [" << username << "] 密码错误" << std::endl;
        return false;
    }
    else{
        std::cout << GetLocalTime() << "用户 [" << username << "] 不存在" << std::endl;
        return false;
    }
}

bool isUserExisting(string username, UserList* default_userlist){
    if(default_userlist->search_user(username)){
        return true;
    }
    else{
        return false;
    }
}
