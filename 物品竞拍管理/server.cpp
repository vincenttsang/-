//
//  server.cpp
//  物品竞拍管理服务端
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include "item.hpp"
#include "multi-user.hpp"
#include "utilities.hpp"
using string = std::string;
using json = nlohmann::json;
using std::cout;
using std::endl;

//Functions From server.cpp:
void InitializeConfig(void);

//Functions From utilities.cpp:
bool isFileExist(const std::string& name);
void GenerateUUID(string &id);
void clear(void);
std::string GetLocalTime(void);

//Functions From communication.cpp:
int RunServer();

UserList* default_userlist = new UserList;

int main(int argc, const char * argv[]){
    // insert code here...
    if(!isFileExist("config.json")){
        cout << GetLocalTime() << "配置文件不存在" << endl;
        InitializeConfig();
        cout << GetLocalTime() << "已生成配置文件" << endl;
    }
    cout << GetLocalTime() << "从config.json读取设置" << endl;
    if(!isFileExist("saves")){
        cout << GetLocalTime() <<  "新建用户文件目录" << endl;
        mkdir("saves", 0755); //创建目录权限为755
        chdir("saves");
    }
    else{
        chdir("saves");
        cout << GetLocalTime() <<  "已找到用户文件目录" << endl;
        cout << GetLocalTime() <<  "开始读取物品资料" << endl;
        
    }
    RunServer();
    return 0;
}

void InitializeConfig(void){
    json config;
    config["First Run"] = "true";
    config["Mode"] = 0;
    config["Items"] = 0;
    config["Encypted"] = 0;
    std::ofstream config_file;
    config_file.open("config.json");
    config_file << std::setw(4) << config << std::endl;
    config_file.close();
}
