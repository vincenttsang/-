//
//  communication.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "communication.hpp"
#include "item.hpp"
#include "multi-user.hpp"
#include "utilities.hpp"

using std::vector;

extern UserList* default_userlist;
extern vector<Item*> item_ptr_vector;
extern bool out_of_time;
extern unsigned long new_price;

std::string data_in_string;
unsigned long seconds = 0;

void tcp_connection::ProcessRequest(std::string str){
    int opcode = 0;
    
    // 将std::string请求变为json对象
    
    json request;
    try {
        request = json::parse(str);
        opcode = request["opcode"];
    }
    catch (json::parse_error& ex) {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }
    
    // opcode 0 登录
    
    if(opcode == 0){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string password = request["token"];
            
            if(UserLogin(username, password, default_userlist)){
                std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                response["response_code"] = 1; // 1 For SUCCESS
            }
            else{
                response["response_code"] = 0;
                std::cout << GetLocalTime() << "用户 [" << username << "] 登录失败" << std::endl;
            }
            data_in_string = JsonToString(response); // 将要在do_write()回应客户端的内容
        }
        catch (json::parse_error& ex) {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
    }
    
    // opcode 114514 新用户注册
    
    if(opcode == 114514){
        try {
            std::string username = request["username"];
            std::string password = request["token"];
            json response;
            response["response_code"] = 0; // 0 For ERROR
            
            if(isUserExisting(username, default_userlist)){
                std::cout << GetLocalTime() << "注册失败 用户 [" << username << "] 已存在" << std::endl;
                response["response_code"] = 0; // 用户已存在
            }
            else{
                default_userlist->add_user(username, password, false); // 默认非管理员账户
                response["response_code"] = 1;
                default_userlist->SaveToDisk();
            }
            data_in_string = JsonToString(response);
        }
        catch (json::parse_error& ex) {
            std::cerr << "parse error at byte " << ex.byte << std::endl;
        }
    }
    
    // opcode 1 录入物品
    
    if(opcode == 1){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string name = request["name"];
            std::string condition = request["condition"];
            std::string info = request["info"];
            std::string filename;
            item_condition_num condition_in_num = request["condition_in_num"];
            
            GenerateFileName(filename); // 生成文件名
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品名 [" << request["name"] << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品介绍 [" << request["info"] << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品新旧程度描述 [" << request["condition"] << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品新旧程度数值 [" << request["condition_in_num"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [录入物品信息]" << std::endl;
            if(UserLogin(username, token, default_userlist)){
                data_in_string = "服务器: 登录成功";
                std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                Item new_item;
                std::string new_uuid;
                GenerateUUID(new_uuid);
                std::cout << GetLocalTime() << "给予物品新UUID：" << new_uuid << std::endl;
                new_item.set_item_name(name);
                new_item.set_item_owner(username);
                new_item.set_item_condition(condition);
                new_item.set_item_introduction(info);
                new_item.set_item_condition_in_number(condition_in_num);
                new_item.set_item_uuid(new_uuid);
                new_item.SaveToDisk(filename);
                LoadAnItem(filename); // 将新的物品对象放入内存并将地址放入指针容器中
                response["response_code"] = 1;
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 登录失败" << std::endl;
            }
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 2 修改物品
    
    if(opcode == 2){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            std::string name = request["name"];
            std::string condition = request["condition"];
            std::string info = request["info"];
            std::string filename;
            item_condition_num condition_in_num = request["condition_in_num"];
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [修改物品信息]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL && (item->show_item_owner()) == username){
                    std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    item->set_item_name(name);
                    item->set_item_owner(username);
                    item->set_item_condition(condition);
                    item->set_item_introduction(info);
                    item->set_item_condition_in_number(condition_in_num);
                    item->SaveToDisk(filename);
                    response["response_code"] = 1;
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 修改物品失败" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 3 删除物品
    
    if(opcode == 3){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            std::string filename;
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [删除物品]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL && (item->show_item_owner()) == username){
                    item_ptr_vector.erase(remove(item_ptr_vector.begin(),item_ptr_vector.end(),item),item_ptr_vector.end());
                    std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    response["response_code"] = 1;
                    response["name"] = item->show_item_name();
                    SaveAllItemsToFiles();
                    delete item;
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 删除物品失败" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 4 输出指定物品信息
    
    if(opcode == 4){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            std::string filename;
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [输出指定物品信息]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL && (item->show_item_owner()) == username){
                    std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    response["response_code"] = 1;
                    response["name"] = item->show_item_name();
                    response["owner"] = item->show_item_owner();
                    response["info"] = item->show_item_info();
                    response["condition"] = item->show_item_condition();
                    response["condititon_in_num"] = item->show_item_condition_in_number();
                    response["price"] = item->show_item_price();
                    response["started_auction"] = item->is_auction_started();
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 查询物品失败" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 44 查询竞拍状态
    
    if(opcode == 44){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            std::string filename;
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [查询竞拍状态]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL){
                    std::cout << GetLocalTime() << "用户 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    response["response_code"] = 1;
                    response["name"] = item->show_item_name();
                    response["owner"] = item->show_item_owner();
                    response["price"] = item->show_item_price();
                    response["started_auction"] = item->is_auction_started();
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 查询竞拍状态失败" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 5 开始拍卖
    
    if(opcode == 5){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            seconds = request["seconds"];
            std::string filename;
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [开始拍卖]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL && isAdminUser(username, default_userlist)){
                    std::cout << GetLocalTime() << "管理员 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    item->start_auction();
                    item->SaveToDisk(filename);
                    std::thread timer_thr(timer, seconds, std::ref(out_of_time));
                    timer_thr.detach();
                    response["response_code"] = 1;
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 不能开始拍卖" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 6 拍卖出价
    
    if(opcode == 6){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            std::string uuid = request["uuid"];
            new_price = request["price"];
            std::string filename;
            
            std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
            std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
            std::cout << GetLocalTime() << "来自客户端的物品UUID [" << request["uuid"] << "]" << std::endl;
            std::cout << GetLocalTime() << "客户端请求的操作模式为 [拍卖出价]" << std::endl;
            
            if(UserLogin(username, token, default_userlist)){
                Item* item = NULL;
                item = SearchInPtrVector(uuid, filename);
                if(item != NULL && out_of_time == false){
                    std::cout << GetLocalTime() << "客户 [" << username << "] 登录成功" << std::endl;
                    std::cout << GetLocalTime() << "物品UUID：" << item->show_item_uuid() << std::endl;
                    if((item->show_item_price()) < new_price){
                        item->set_item_price(new_price);
                        item->set_item_owner(username);
                        item->SaveToDisk(filename);
                        response["response_code"] = 1;
                    }
                    else{
                        response["response_code"] = 0;
                    }
                }
                else{
                    response["response_code"] = 0;
                }
            }
            else{
                std::cout << GetLocalTime() << "用户 [" << username << "] 不能开始拍卖" << std::endl;
            }
            
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
    // opcode 7 管理员查询所有物品
    
    if(opcode == 7){
        json response;
        response["response_code"] = 0; // 0 For ERROR
        
        try {
            std::string username = request["username"];
            std::string token = request["token"];
            int started = request["started"];
            if(isAdminUser(username, default_userlist) && UserLogin(username, token, default_userlist)){
                if(started == 1){
                    Item* item_ptr= NULL;
                    std::string uuid_from_item;
                    for (int i = 0; i < item_ptr_vector.size(); i++){
                        item_ptr = item_ptr_vector[i];
                        response["uuid"] = item_ptr->show_item_uuid();
                        response["name"] = item_ptr->show_item_name();
                        response["owner"] = item_ptr->show_item_owner();
                        
                        if(i + 1 >= item_ptr_vector.size()){
                            response["end"] = true;
                        }
                        else{
                            response["end"] = false;
                        }
                        
                        response["response_code"] = 1;
                    }
                    
                }
                else{
                    std::cout << GetLocalTime() << "来自客户端的用户名 [" << username << "]" <<std::endl;
                    std::cout << GetLocalTime() << "来自客户端的用户密码 [" << token << "]" << std::endl;
                    std::cout << GetLocalTime() << "客户端请求的操作模式为 [管理员查询所有物品]" << std::endl;
                    response["response_code"] = 1;
                }
            }
            else{
                response["response_code"] = 0;
                std::cout << GetLocalTime() << "用户 [" << username << "] 不存在或不是管理员 无法执行 [管理员查询所有物品] 操作" <<std::endl;
            }
            data_in_string = JsonToString(response);
        }
        
        catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
    }
    
}



void tcp_connection::do_read(void){
    buffer_ = new char[BUFFER_SIZE]();
    socket_.async_read_some(boost::asio::buffer(buffer_, BUFFER_SIZE),
                            boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
    data_in_string.assign(buffer_);
    delete [] buffer_;
    //std::cout << GetLocalTime() << "从客户端收到请求：" << data_in_string << std::endl;
    std::cout << GetLocalTime() << "收到客户端请求" << std::endl;
    
}

void tcp_connection::do_write(std::string str){
    message_ = str; //回应客户端
    
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
    std::cout << GetLocalTime() << "已发送：" << this->message_ << std::endl;
}

int RunServer(){
    try {
      boost::asio::io_context io_context;
      tcp_server server(io_context);
      io_context.run();
    }
    catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    return 0;
}
