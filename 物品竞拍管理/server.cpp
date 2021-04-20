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
#include "item.hpp"
using string = std::string;
using json = nlohmann::json;
using std::cout;
using std::endl;

//Functions From server.cpp:
void CreateNewItem(Item *item);
void SaveItemToDisk();
void LoadItemFromDisk();
void InitializeConfig(void);

//Functions From utilities.cpp:
bool isFileExist(const std::string& name);
void GenerateUUID(string &id);
void clear(void);

//Functions From communication.cpp:
int server();

int main(int argc, const char * argv[]){
    // insert code here...
    string tmp;
    GenerateUUID(tmp);
    std::cout << tmp << std::endl;
    if(!isFileExist("config.json")){
        cout << "配置文件不存在" << endl;
        InitializeConfig();
        cout << "已生成配置文件" << endl;
        server();
    }
    else{
        cout << "从config.json读取设置" << endl;
        server();
    }
    return 0;
}

void CreateNewItem(Item *item){
    item = new Item;
}

void LoadItemFromDisk(){
    
}

void SaveItemToDisk(){
    
}

void InitializeConfig(void){
    json config;
    config["First Run"] = "true";
    config["Mode"] = 0;
    config["Items"] = 0;
    config["Encypted"] = 0;
    std::ofstream config_file;
    config_file.open("config.json");
    config_file << config << std::endl;
    config_file.close();
}
