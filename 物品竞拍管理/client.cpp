//
//  client.cpp
//  物品竞拍管理客户端
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "client.hpp"

client_tcp_connection::client_tcp_connection(){
    _socket = new tcp::socket(_io);
    _endpoint = new tcp::endpoint(boost::asio::ip::address::from_string(ip_address), 11451);
}

void client_tcp_connection::client_send(json j){
    try {
        std::string data = j.dump();
        this->_socket->connect(*(this->_endpoint));
        
        boost::system::error_code ec;
        this->_socket->write_some(boost::asio::buffer(data), ec); // 发送数据
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

void client_tcp_connection::client_recv(){
    try {
        boost::array<char, 81920> buf;
        boost::system::error_code error;
        size_t len = this->_socket->read_some(boost::asio::buffer(buf), error);
        
        this->data_from_server.assign(buf.data(), len);
        cout << this->data_from_server << endl;
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

void client_tcp_connection::client_process_data(bool& result){
    json response_from_server;
    int response_code;
    try {
        response_from_server = json::parse(this->data_from_server);
        response_code = response_code_from_server["response_code"];
        if(response_code == 1){
            result = true;
        }
        if(response_code == 0){
            result = false;
        }
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

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
                cout << "感谢使用" << endl;
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
                    cout << "用户注册成功 请登录注册的账户" << endl;
                    return ERROR;
                }
                else{
                    cout << "用户注册失败" << endl;
                    return ERROR;
                }
                break;
            case 3:
                cout << "感谢使用" << endl;
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
    bool result;
    login["opcode"] = 0; // 0为登录opcode
    login["username"] = username;
    login["token"] = password;
    client_tcp_connection* new_connection = new client_tcp_connection();
    new_connection->client_send(login);
    new_connection->client_recv();
    new_connection->client_process_data(result);
    delete new_connection;
    return result;
}

bool ClientRegisterUser(std::string username, std::string password){
    json reg;
    bool result;
    reg["opcode"] = 114514; // 0为登录opcode
    reg["username"] = username;
    reg["token"] = password;
    client_tcp_connection* new_connection = new client_tcp_connection();
    new_connection->client_send(reg);
    new_connection->client_recv();
    new_connection->client_process_data(result);
    delete new_connection;
    return result;
}

void RecordInformation(void){
    json new_item;
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
    new_item["opcode"] = 1;
    new_item["username"] = username;
    new_item["token"] = password;
    new_item["name"] = name;
    new_item["info"] = info;
    new_item["condition_in_num"] = condition_num;
    new_item["condition"] = condition;
    client_tcp_connection* new_connection = new client_tcp_connection();
    new_connection->client_send(new_item);
}
