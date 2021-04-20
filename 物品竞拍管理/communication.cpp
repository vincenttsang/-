//
//  communication.cpp
//  物品竞拍管理
//
//  Created by Vincent Tsang on 15/4/2021.
//

#include "communication.hpp"
#include <iostream>
#include <string>

int RunServer(){
    try
    {
      boost::asio::io_context io_context;
      tcp_server server(io_context);
      io_context.run();
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
    return 0;
}
