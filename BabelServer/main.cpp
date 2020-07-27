/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

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
    while (std::cin.getline(data, 10 + 1)) {
        std::cout << "loop" << std::endl;
    }
}

static void response_testing()
{
    BabelNetwork::ConnectionResponse lol;
    std::cout << "After init: " << lol << std::endl;
    lol.setOk();
    std::cout << "After setOk: " << lol << std::endl;
    lol.encode_header();
    std::cout << "After encodeHeader: " << lol << " length: " << lol.getHeaderDataLength() << std::endl;
    lol.decode_header();
    std::cout << "After decodeHeader: " << lol << " length: " << lol.getHeaderDataLength() << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    BabelNetwork::AResponse::ResponseHeader header{
        .returnCode = BabelNetwork::IResponse::ResponseCode::LoginOk,
        .dataLength = 5};
    BabelNetwork::ConnectionResponse lol2(&header);
    std::cout << "After init: " << lol2 << std::endl;
    lol2.encode_header();
    std::cout << "After encodeHeader: " << lol2 << " length: " << lol2.getHeaderDataLength() << std::endl;
    lol2.decode_header();
    std::cout << "After decodeHeader: " << lol2 << " length: " << lol2.getHeaderDataLength() << std::endl;
    lol2.setOk();
    std::cout << "After setOk: " << lol2 << std::endl;
    lol2.encode_header();
    std::cout << "After encodeHeader: " << lol2 << " length: " << lol2.getHeaderDataLength() << std::endl;
    lol2.decode_header();
    std::cout << "After decodeHeader: " << lol2 << " length: " << lol2.getHeaderDataLength() << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    try {
//        start(av);
//        tests(av);
        response_testing();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}