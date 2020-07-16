#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
#include "Server.hpp"
#include <functional>
#include "Socket.hpp"
#include "BoostThread.hpp"
#include "ServerListener.tpp"

void launch(char **av);

static void tests(char **av)
{
    std::cout << "TEST LAUNCHED" << std::endl;
    BabelNetwork::NetworkInfos nwi;
    try {
        auto ip = boost::asio::ip::address::from_string(av[1]);
        nwi.setIp(ip.to_string());
    } catch (const std::exception &e) {
        nwi.setIp(boost::asio::ip::address_v4().to_string());
    }
    std::cout << nwi << std::endl;

    BabelNetwork::AsioSocket<BabelNetwork::Listener> listener(nwi);
//    listener.start();

//    listener.getContext()->run();

//    listener.setThread(
//        boost::make_shared<BabelUtils::BoostThread>(
//            [ObjectPtr = &listener] {
//                std::cout << "THREAD LAUNCHED" << std::endl;
//                ObjectPtr->getContext()->run();
//                std::cout << "THREAD FINISHED" << std::endl;
//            }
//        )
//    );
    char data[10] = {0};
    while (std::cin.getline(data, 10+ 1)) {
        std::cout << "loop" << std::endl;
    }
//    int value = 14;
//    BabelUtils::BoostThread<boost::thread, std::function<void (int)>> thread(&lolfunc2, value);
//    thread.start();
//    BabelUtils::BoostThread<boost::thread, std::function<void (int)>> thread2(lolfunc2);
//    thread2.setHandler(boost::bind(&lolfunc2, value));
//    thread2.start(value);


//    boost::asio::io_context io_context;
//    boost::asio::ip::tcp::resolver resolver(io_context);
//    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(nwi.getIp(), std::to_string(nwi.getPort()));
//    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), nwi.getPort());


//    BabelServer::Socket socket1(nwi);
//    socket1.start();

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
//        start(av);
        tests(av);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}