//
//  auction.hpp
//  物品竞拍管理服务端
//
//  Created by Vincent Tsang on 7/5/2021.
//

#ifndef auction_hpp
#define auction_hpp

#include <stdio.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <nlohmann/json.hpp>
#include "item.hpp"
using json = nlohmann::json;

void AuctionProc(std::string uuid);
void timer(unsigned int time, bool& out_of_time);
bool UpdatePrice(Item* item, unsigned long new_price);

#endif /* auction_hpp */
