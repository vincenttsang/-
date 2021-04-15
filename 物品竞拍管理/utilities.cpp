//
//  utilities.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include <uuid/uuid.h> //在macOS与Linux平台上的UUID头文件，不兼容Windows
#include <string>
#include <cstdio>
using std::string;

void GenerateUUID(string &id){
    char* id_string_in_c_style = new char[200]();
    uuid_t uuid;
    uuid_generate(uuid);
    for(int i = 0; i < 16; i++){
        sprintf(id_string_in_c_style + i*2, "%02X", uuid[i]); //16进制数转字符
    }
    id = id_string_in_c_style;
} //生成UUID并转换为字符串
