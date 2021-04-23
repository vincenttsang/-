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
#include "utilities.hpp"

typedef struct user{
    std::string name;
    std::string password;
}user;

class UserList{
public:
    UserList(void);
    ~UserList(void);
    bool add_user(std::string username, std::string password);
    bool search_user(std::string username);
    bool user_login(std::string username, std::string password);
private:
    std::vector<user> user_list;
};

bool UserLogin(std::string username, std::string token, UserList* default_userlist);
bool isUserExisting(std::string username, UserList* default_userlist);

#endif /* multi_user_hpp */
