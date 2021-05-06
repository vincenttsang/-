//
//  multi-user.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 20/4/2021.
//

#include "multi-user.hpp"
using string = std::string;

bool UserList::add_user(std::string username, std::string password, bool administrator){
    if(!search_user(username)){
        user new_user;
        new_user.name = username;
        new_user.password = password;
        new_user.administrator = administrator;
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
    // this->add_user("邓佳佳", "114514", true); // Debug用 正式发布要删掉
    // this->add_user("曾文翼", "1919810", true);
}

UserList::~UserList(void){
    
}

void UserList::SaveToDisk(void){
    json obj;
    std::ofstream obj_file;
    std::ofstream user_name;
    user_name.open("users.conf", std::ios::app | std::ios::in);
    std::string filename;
    unsigned long j = user_list.size();
    for(unsigned long i = 0; i<j; i++){
        user_name << this->user_list[i].name << std::endl;
        filename = this->user_list[i].name;
        filename  += ".json";
        obj["username"] = this->user_list[i].name;
        obj["password"] = this->user_list[i].password;
        obj["administrator"] = this->user_list[i].administrator;
        obj_file.open(filename);
        obj_file << std::setw(4) << obj << std::endl;
        obj_file.close();
    }
}

void UserList::ReadFromDisk(void){
    if(isFileExist("users.conf")){
        std::string filename;
        std::ifstream user_name;
        std::ifstream obj_file;
        user_name.open("users.conf", std::ios::in);
        while(!user_name.eof()){
            std::getline(user_name, filename);
            if(filename == "" || filename == "\n"){
                break;
            }
            filename += ".json";
            obj_file.open(filename);
            json obj = json::parse(obj_file);
            std::string username = obj["username"];
            std::string password = obj["password"];
            bool administrator = obj["administrator"];
            this->add_user(username, password, administrator);
            obj_file.close();
        }
    }
    else{
        std::ofstream new_userconf("users.conf");
        new_userconf.close();
    }
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
