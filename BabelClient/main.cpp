/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "Debug.hpp"
#include "AsioClientSocket.hpp"
#include "ConnectionResponse.hpp"

static void socket_testing(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    boost::asio::io_context context;
    boost::shared_ptr<BabelNetwork::AsioClientSocket> client(new BabelNetwork::AsioClientSocket(av[1], av[2], context, BabelNetwork::AsioClientSocket::SocketHandler::Client));
    client->connect();
    client->setThread(boost::make_shared<BabelUtils::BoostThread>(
        [&client] {
            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
            client->getContext().run();
        }
        )
    );
    sleep(1);
    if (!client->isReady()) {
        client->stop();
        throw std::runtime_error("Socket not ready, please check your adresse and ports");
    }

    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        BabelNetwork::ConnectionResponse test;
        test.setOk();
        client->sendResponse(test);
        std::cout << "loop" << std::endl;
    }
}

int main(int ac, char **av)
{
    std::cout << "Babel client!" << std::endl;
    dbg("%s", "DEBUG");
    #ifdef _DEBUG_
    std::cerr << "Debug Mode" << std::endl;
    #endif
    #ifdef _BABEL_LOG_
    std::cerr << "Log Mode" << std::endl;
    #endif
    socket_testing(av);
    return 0;
}
