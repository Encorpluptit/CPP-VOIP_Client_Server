#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
//#include "TcpSocket.hpp"
#include "Server.hpp"
#include <functional>
#include <boost/bind.hpp>
#include "Socket.hpp"
#include "BoostThread.hpp"

void launch(char **av);

void handle_connect(const boost::system::error_code &error)
{
    if (!error)
        std::cout << "Connected" << std::endl;
    else
        std::cerr << "ERROR" << std::endl;
}

void lolfunc()
{

}

static void tests(char **av)
{
    std::cout << "TEST LAUNCHED" << std::endl;
    boost::asio::io_context io_context;
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    std::cout << nwi << std::endl;

    std::function<void ()> lol = lolfunc;
    BabelUtils::BoostThread<boost::thread, std::function<void ()>> thread(10, lolfunc);

    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(nwi.getIp(), std::to_string(nwi.getPort()));
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), nwi.getPort());

    BabelServer::Socket socket1(nwi);
    socket1.launch();
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