/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
#include "NetworkError.hpp"
#include "AsioClientSocket.hpp"
#include "UserResponse.hpp"

static void socket_testing(char **av)
{
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);
    boost::asio::io_context context;
    BabelUtils::Logger logger(BabelUtils::Logger::LogType::ClientLog);

    auto client = boost::make_shared<BabelNetwork::AsioClientSocket>(
            av[1],
            av[2], logger,
            context,
            BabelNetwork::AsioClientSocket::SocketHandler::Client
    );

    client->connect();
    client->setThread(boost::make_shared<BabelUtils::BoostThread>(
        [&client] {
            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
            client->getContext().run();
            std::cout << "CLIENT THREAD FINISHED" << std::endl;
        })
    );

    sleep(1);
    if (!client->isReady()) {
        client->stop();
        throw BabelErrors::NetworkError("Socket not ready, please check your adresse and ports");
    }

    std::string data;
    while (std::getline(std::cin, data)) {
        std::cout << data << std::endl;
        if (data == "exit") {
            std::cout << "exit loop" << std::endl;
            break;
        }
        BabelNetwork::UserResponse test("damien", "abcd1234");
        std::cout << "sending response" << test << std::endl;
        client->sendResponse(test);
        for (int i = 0; i < 100; ++i)
            client->sendResponse(test);
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
