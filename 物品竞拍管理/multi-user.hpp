//
//  multi-user.hpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 20/4/2021.
//

#ifndef multi_user_hpp
#define multi_user_hpp

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <nlohmann/json.hpp>

bool isFileExist(const std::string& name);
void GenerateUUID(std::string &id);
void clear(void);
std::string GetLocalTime(void);

class UserList{
public:
    UserList(void);
    ~UserList(void);
    bool add_user(std::string username);
    bool search_user(std::string username);
private:
    std::vector<std::string> user_list;
};

bool UserList::add_user(std::string username){
    if(!search_user(username)){
        this->user_list.push_back(username);
        return true;
    }
    else{
        std::cout << "用户已存在" << std::endl;
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
                return true;
            } // compare函数返回值为0时字符串匹配成功
        }
        return false;
    }
}

#endif /* multi_user_hpp */
