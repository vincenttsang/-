//
//  utilities.hpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 23/4/2021.
//

#ifndef utilities_hpp
#define utilities_hpp

#include <uuid/uuid.h> //在macOS或Linux平台上用于生成UUID
#include <sys/stat.h>
#include <string>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include "item.hpp"

bool isFileExist(const std::string& name);
void GenerateUUID(std::string &id);
void GenerateFileName(std::string &name);
void clear(void);
std::string GetLocalTime(void);
Item* SearchInPtrVector(std::string uuid, std::string &filename);
void LoadItemsFromFiles(void);
void LoadAnItem(std::string filename);
void SaveAllItemsToFiles(void);

#endif /* utilities_hpp */
