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
    boost::shared_ptr<BabelNetwork::AsioClientSocket> client(new BabelNetwork::AsioClientSocket(nwi, context));
    client->connect();
    client->setThread(boost::make_shared<BabelUtils::BoostThread>(
        [&client] {
            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
            client->getContext().run();
        }
        )
    );
//    client->connect();
//    BabelNetwork::AsioClientSocket client(nwi, context);
//    auto lol = boost::make_shared<BabelNetwork::AsioClientSocket>(client);
//    client.getContext().run();
//    sleep(1);
//    client.connect();
//    client.setThread(boost::make_shared<BabelUtils::BoostThread>(
//        [&client] {
//            std::cout << "CLIENT THREAD LAUNCHED" << std::endl;
//            client.getContext().run();
//        }
//        )
//    );
//
//    sleep(5);
//    for (int i = 0; i < 100; i += 1) {
//        BabelNetwork::ConnectionResponse test;
//        test.setOk();
//        client->sendResponse(test);
//    }
    char data[10] = {0};
    while (std::cin.getline(data, 10 + 1)) {
        BabelNetwork::ConnectionResponse test;
        test.setOk();
        client->sendResponse(test);
        std::cout << "loop" << std::endl;
    }
}

static void response_testing()
{
    BabelNetwork::ConnectionResponse test;
    std::cout << "before encode login = " << test.getLogin() << " password = " << test.getPassword() << std::endl;
    test.encode();
    std::cout << "after encode login = " << test.getLogin() << " password = " << test.getPassword() << std::endl;
    test.decode_header();
    test.decode_data();
    std::cout << "after decode login = " << test.getLogin() << " password = " << test.getPassword() << std::endl;
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
//    response_testing();
    return 0;
}
