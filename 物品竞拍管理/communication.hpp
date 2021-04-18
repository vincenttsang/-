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
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_context;
using json = nlohmann::json;

json CreateRequest(const std::string op, const std::string data);
json StringToJson(const std::string jsonStr);
std::string JsonToString(const json j);

json CreateRequest(const std::string op, const std::string data){
    json request;
    request["Operation"] = op;
    request["Data"] = data;
    return request;
} // For client

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
    
    void do_read(){
        socket_.async_read_some(boost::asio::buffer(message_),
                                boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
        std::cout << "从客户端接收到：" << this->message_ << std::endl;
    }
    
    void do_write(){
        message_ = Respond("test data");
        
        boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
        std::cout << "已发送：" << this->message_ << std::endl;
    }
    
private:
    tcp_connection(boost::asio::io_context& io_context)
    : socket_(io_context){
        
    }
    
    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/){
        
    }
    
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
