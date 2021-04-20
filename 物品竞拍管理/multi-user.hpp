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

#endif /* multi_user_hpp */
