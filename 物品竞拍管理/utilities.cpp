//
//  utilities.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "utilities.hpp"

using std::string;
using std::vector;

vector<Item*> item_ptr_vector;

void GenerateUUID(string &id){
    char* id_string_in_c_style = new char[200]();
    uuid_t uuid;
    uuid_generate(uuid);
    for(int i = 0; i < 16; i++){
        sprintf(id_string_in_c_style + i*2, "%02X", uuid[i]); //16进制数转字符
    }
    id = id_string_in_c_style;
} //生成UUID并转换为字符串

bool isFileExist(const std::string& name){
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
} //使用POSIX stat方式检测文件存在

void clear(void){
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

string GetLocalTime(void){
    std::array<char, 64> buffer;
    buffer.fill(0);
    time_t rawtime;
    time(&rawtime);
    const auto timeinfo = localtime(&rawtime);
    strftime(buffer.data(), sizeof(buffer), "[%Y/%m/%d %H:%M:%S] ", timeinfo);
    string timeStr(buffer.data());
    return timeStr;
}

void GenerateFileName(string &name){
    int i = 0;
    std::string test_name = std::to_string(i);
    test_name += ".item.json";
    while(isFileExist(test_name) == true){
        i += 1;
        test_name = std::to_string(i);
        test_name += ".item.json";
    }
    name = std::to_string(i);
}

void LoadItemsFromFiles(void){
    int i = 0;
    Item* item_ptr = NULL;
    std::string test_name = std::to_string(i);
    test_name += ".item.json";
    while(isFileExist(test_name) == true){
        item_ptr = new Item;
        item_ptr->ReadFromDisk(test_name);
        item_ptr_vector.push_back(item_ptr);
        i += 1;
        test_name = std::to_string(i);
        test_name += ".item.json";
    }
}

void SaveAllItemsToFiles(void){
    int i = 0;
    Item* item_ptr;
    std::string test_name = std::to_string(i);
    std::string filename;
    test_name += ".item.json";
    while(isFileExist(test_name) == true){
        std::remove(test_name.c_str());
        i += 1;
        test_name = std::to_string(i);
        test_name += ".item.json";
    }
    
    for (int i = 0; i < item_ptr_vector.size(); i++){
        item_ptr = item_ptr_vector[i];
        filename = std::to_string(i);
        item_ptr->SaveToDisk(filename);
    }
}

void LoadAnItem(std::string filename){
    Item* item_ptr = NULL;
    item_ptr = new Item;
    filename += ".item.json";
    item_ptr->ReadFromDisk(filename);
    item_ptr_vector.push_back(item_ptr);
}

Item* SearchInPtrVector(std::string uuid, std::string &filename){
    Item* item_ptr = NULL;
    std::string uuid_from_item;
    
    for (int i = 0; i < item_ptr_vector.size(); i++){
        item_ptr = item_ptr_vector[i];
        uuid_from_item = item_ptr->show_item_uuid();
        filename = std::to_string(i);
        if(uuid_from_item.compare(uuid) == 0){
            break;
        }
        else{
            item_ptr = NULL;
        }
    }
    
    return item_ptr;
}
