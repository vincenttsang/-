//
//  client.hpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 22/4/2021.
//

#ifndef client_hpp
#define client_hpp

#define ERROR -255;
#define SUCCESS 255;

#include <iostream>
#include <string>
#include <cstdio>
#include <nlohmann/json.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "utilities.hpp"

using boost::asio::ip::tcp;
using boost::asio::io_context;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using json = nlohmann::json;

int UserMenu(void);
int BidMenu(void);
bool ClientUserLogin(std::string username, std::string password);
bool ClientRegisterUser(std::string username, std::string password);
bool AdminLoadItems(void);

//Functions From client.cpp:
bool RecordInformation(void);
bool EditInformation(void);
bool DeleteInformation(void);
bool ShowItemInformation(void);
bool StartAuction(void);

std::string ip_address = "127.0.0.1";
std::string username;
std::string password;

class client_tcp_connection{
public:
    client_tcp_connection();
    void client_send(json j);
    void client_recv();
    void client_process_data(bool& result);
    json show_recv_json();
private:
    boost::asio::io_service _io;
    tcp::endpoint* _endpoint;
    tcp::socket* _socket;
    std::string data_from_server;
    json response_from_server;
};

#endif /* client_hpp */
