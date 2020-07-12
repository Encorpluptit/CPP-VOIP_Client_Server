#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
#include "TcpSocket.hpp"

void launch();

int main()
{
    BabelNetwork::NetworkInfos lol("127.0.0.1");
    BabelNetwork::ConnectionResponse conn;
    std::cout << conn << std::endl;
    std::cout << lol << std::endl;
    boost::asio::io_context io_context;
//    boost::asio::io_context();
//    boost::asio::ip::tcp::socket _socket;
    BabelNetwork::TcpSocket sock(io_context);

//    BabelNetwork::ConnectionResponse resp;
//    std::cout << resp.serialize() << std::endl;
//    std::cout << resp << std::endl;
//    try {
//        launch();
//    }
//    catch (std::exception &e) {
//        std::cerr << e.what() << std::endl;
//    }
//    return 0;
}