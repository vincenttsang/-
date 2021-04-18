//
//  client.cpp
//  物品竞拍管理客户端
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include <iostream>
#include <string>
#include <cstdio>
using std::string;
using std::cout;
using std::cin;
using std::endl;

void RecordInformation();

void clear(void);

int main(int argc, const char * argv[]){
    int op = 1;
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
                op = -1;
                break;
            default:
                clear();
                cin.clear();
                fflush(stdin);
                op = -1;
                break;
        }
    }
    return 0;
}

void RecordInformation(){
    string name,condition,info;
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
}
