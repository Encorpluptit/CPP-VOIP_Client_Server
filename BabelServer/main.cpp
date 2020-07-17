#include <iostream>
#include "Debug.hpp"
#include "ConnectionResponse.hpp"
#include "Logger.hpp"
#include "NetworkInfos.hpp"
#include "Server.hpp"
#include <functional>
#include "Socket.hpp"
#include "BoostThread.hpp"
#include "Listener.tpp"

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

    boost::asio::io_context context;
    BabelServer::Listener listener(context, nwi);

    char data[10] = {0};
    while (std::cin.getline(data, 10+ 1)) {
        std::cout << "loop" << std::endl;
    }
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