//
//  communication.hpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#ifndef communication_hpp
#define communication_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <nlohmann/json.hpp>
#include "item.hpp"
#include "multi-user.hpp"
#define BUFFER_SIZE 81920

using boost::asio::ip::tcp;
using boost::asio::io_context;
using json = nlohmann::json;

json StringToJson(const std::string jsonStr);
std::string JsonToString(const json j);

// Functions from utilities.cpp:
void GenerateUUID(std::string &id);


std::string Respond(const std::string data){
    return data;
}

json StringToJson(const std::string jsonStr){
    json j = json::parse(jsonStr);
    return j;
}

std::string JsonToString(const json j){
    std::string json_in_str = j.dump();
    return json_in_str;
}

std::string request_in_string(std::string str){
    return str;
}

class tcp_connection
: public boost::enable_shared_from_this<tcp_connection>{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    
    static pointer create(boost::asio::io_context& io_context){
        return pointer(new tcp_connection(io_context));
    }
    
    tcp::socket& socket(){
        return socket_;
    }
    void ProcessRequest(std::string str);
    
    void do_read();
    
    void do_write();
    
private:
    tcp_connection(boost::asio::io_context& io_context)
    : socket_(io_context){
        
    }
    
    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/){
        
    }
    
    char* buffer_;
    std::string data_in_string;
    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
    tcp_server(boost::asio::io_context& io_context)
    : io_context_(io_context),
    acceptor_(io_context, tcp::endpoint(tcp::v4(), 11451)){
        start_accept();
    }
    
private:
    void start_accept(){
        tcp_connection::pointer new_connection =
        tcp_connection::create(io_context_);
        
        acceptor_.async_accept(new_connection->socket(),boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
    }
    
    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error){
        if (!error){
            new_connection->do_read();
            new_connection->do_write();
        }
        
        start_accept();
    }
    
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};
#endif /* communication_hpp */
