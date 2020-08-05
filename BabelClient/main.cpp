/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "NetworkError.hpp"
#include "AsioClientSocket.hpp"
#include "ConnectionResponse.hpp"

static void socket_testing(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    boost::asio::io_context context;
    BabelUtils::Logger logger(BabelUtils::Logger::LogType::ClientLog);
    boost::shared_ptr<BabelNetwork::AsioClientSocket> client(
        new BabelNetwork::AsioClientSocket(
            av[1],
            av[2], logger,
            context,
            BabelNetwork::AsioClientSocket::SocketHandler::Client)
    );
//    client->connect();
    client->setThread(boost::make_shared<BabelUtils::BoostThread>(
        [&client] {
            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
            client->connect();
//            client->getContext().run();
            std::cout << "CLIENT THREAD FINISHED" << std::endl;
        }
        )
    );
    sleep(1);
    if (!client->isReady()) {
        client->stop();
        throw BabelErrors::NetworkError("Socket not ready, please check your adresse and ports");
    }

    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        BabelNetwork::ConnectionResponse test;
        test.setOk();
        for (int i = 0; i < 100; ++i)
            client->sendResponse(test);
        std::cout << "loop" << std::endl;
    }
    client->stop();
}

int main(int ac, char **av)
{
    if (ac < 3)
        return 84;
    std::cout << "Babel client!" << std::endl;
    try {
        socket_testing(av);
    } catch (const BabelErrors::BabelError &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
