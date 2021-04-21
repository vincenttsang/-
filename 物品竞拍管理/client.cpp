//
//  client.cpp
//  物品竞拍管理客户端
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <nlohmann/json.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::io_context;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using json = nlohmann::json;

#define ERROR -255;
#define SUCCESS 255;
int UserMenu(void);
bool ClientUserLogin(std::string username, std::string password);
bool ClientRegisterUser(void);

//Functions From client.cpp:
void RecordInformation(void);
void send(json j);
//Functions From utilities.cpp:
bool isFileExist(const std::string& name);
void GenerateUUID(string &id);
void clear(void);

std::string ip_address = "127.0.0.1";
std::string username;
std::string password;

int main(int argc, const char * argv[]){
    for(;UserMenu()!=SUCCESS);
    int op = -1;
    while(op != 0){
        cout << "欢迎使用物品竞拍管理系统" << endl << "请从菜单中选择功能：" << endl;
        cout << "1.录入物品信息\n2.修改物品信息\n3.删除物品\n4.显示物品信息\n5.输出指定类型的所有物品" << endl;
        cout << "0.退出程序" << endl;
        cin.clear();
        fflush(stdin);
        scanf("%d", &op);
        switch (op) {
            case 0:
                clear();
                return 0;
                break;
            case 1:
                RecordInformation();
                clear();
                cout << "录入完成\n\n";
                break;
            default:
                clear();
                cin.clear();
                fflush(stdin);
                break;
        }
    }
    return 0;
}

void RecordInformation(void){
    std::string name,condition,info;
    int condition_num = 0;
    cout << "请输入物品信息\n";
    cin.clear();
    fflush(stdin);
    cout << "请输入物品名：";
    getline(cin,name);
    cout << "请输入物品描述：";
    getline(cin,info);
    cout << "请输入物品新旧程度描述：";
    getline(cin,condition);
    cout << "请输入物品新旧程度数（范围0-10，10为十成新，0为战损版，以此类推）：";
    cin >> condition_num;
    json new_item;
    new_item["opcode"] = 1;
    new_item["username"] = username;
    new_item["token"] = password;
    new_item["name"] = name;
    new_item["info"] = info;
    new_item["condition_in_num"] = condition_num;
    new_item["condition"] = condition;
    send(new_item);
}

void send(json j){
    try{
        std::string data = j.dump();
        //(1)通过tcp::socket类定义一个tcp client对象socket
        boost::asio::io_service io;
        tcp::socket socket(io);

        //(2)通过connect函数连接服务器，打开socket连接。
        tcp::endpoint end_point(boost::asio::ip::address::from_string(ip_address), 11451);
        socket.connect(end_point);
        
        boost::system::error_code ec;
        socket.write_some(boost::asio::buffer(data), ec);
        boost::array<char, 128> buf;
        boost::system::error_code error;
        
        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        
        if (error == boost::asio::error::eof)
            std::cout << "Connection closed cleanly by peer." << std::endl;
        else if (error)
            throw boost::system::system_error(error); // Some other error.
        
        std::cout.write(buf.data(), len);
    }
    catch (std::exception& e){
        cout << e.what() << endl;
    }
}

int UserMenu(void){
    int op = -1;
    cout << "欢迎使用物品竞拍管理系统" << endl << "请先登录" << endl;
    while(op != 0){
        cout << "1.用户登录\n2.用户注册\n3.退出程序" << endl;
        cin.clear();
        fflush(stdin);
        scanf("%d", &op);
        cin.clear();
        fflush(stdin);
        switch (op) {
            case 1:
                cout << "请输入用户名：";
                getline(cin,username);
                cout << "请输入用户密码：";
                getline(cin,password);
                if(ClientUserLogin(username, password)){
                    cout << "用户登录成功" << endl;
                    return SUCCESS;
                }
                else{
                    cout << "用户不存在" << endl;
                    return ERROR;
                }
                break;
            case 2:
                if(ClientRegisterUser()){
                    cout << "用户注册成功" << endl;
                    return ERROR;
                }
                else{
                    cout << "用户注册失败" << endl;
                    return ERROR;
                }
                break;
            case 3:
                exit(0);
                break;
            default:
                cin.clear();
                fflush(stdin);
                return ERROR;
                break;
        }
    }
    return ERROR;
}

bool ClientUserLogin(std::string username, std::string password){
    json login;
    login["opcode"] = 0; // 0为登录opcode
    login["username"] = username;
    login["token"] = password;
    login["name"] = 0;
    login["info"] = 0;
    login["condition_in_num"] = 0;
    login["condition"] = 0;
    send(login);
    return true;
}

bool ClientRegisterUser(void){
    return true;
}
