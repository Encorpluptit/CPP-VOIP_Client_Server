#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
#include "TcpSocket.hpp"
#include "Server.hpp"
#include <boost/bind.hpp>
#include "ServerSocket.hpp"


void launch(char **av);

void handle_connect(const boost::system::error_code &error)
{
    std::cout << "Connected" << std::endl;
}
static void tests(char **av)
{
    boost::asio::io_context io_context;

    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(av[1], av[2]);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), atoi(av[2]));

//    boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint);
//    boost::asio::ip::tcp::acceptor acceptor(io_context, endpoints);
//    boost::asio::async_connect(
//        boost::asio::ip::tcp::socket(io_context),
//        endpoints,
//        boost::bind(&chat_client::handle_connect, this, boost::asio::placeholders::error)
//    );
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    try {
//        launch(av);
        tests(av);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}