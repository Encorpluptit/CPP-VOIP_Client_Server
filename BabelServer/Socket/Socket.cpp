/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/13/20).
** File description:
** [Socket.cpp]: Source file for Socket feature.
*/

#include <iostream>
#include "Socket.hpp"

using namespace BabelServer;

Socket::Socket(const BabelNetwork::NetworkInfos &networkInfos)
    : ASocket(networkInfos),
      _socket(_context),
      _acceptor(
          boost::asio::ip::tcp::acceptor(
              _context,
              boost::asio::ip::tcp::endpoint(
                  boost::asio::ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()
              )
          )
      ),
      _signals(_context)
{
    setSocketOptions();
    setSignalsHandeled();
//    _thread = boost::thread([] { std::cout << "THREAD LAUNCHED" << std::endl;});
//    boost::thread _thread([ObjectPtr = &_context] { ObjectPtr->run(); });

//    boost::asio::ip::tcp::endpoint endpoint(
//        boost::asio::ip::address::from_string(_networkInfos.getIp()),
//        _networkInfos.getPort()
//    );
//    _acceptor = boost::asio::ip::tcp::acceptor(_context, endpoint);
}

void Socket::launch()
{
//    _thread = boost::thread([] { std::cout << "THREAD LAUNCHED" << std::endl;});
    _thread = boost::thread([ObjectPtr = &_context, this] {
        std::cout << "THREAD LAUNCHED" << std::endl;
        ObjectPtr->run();
//        this->_thread.join();
        std::cout << "THREAD FINISHED" << std::endl;
    });
//    _thread = boost::thread([this] {
//        std::cout << "THREAD LAUNCHED" << std::endl;
//        this->start_accept();
//        std::cout << "THREAD FINISHED" << std::endl;
//    });
    start_accept();
//    _thread = boost::thread([this] {
//        std::cout << "THREAD LAUNCHED" << std::endl;
//        this->start_accept();
//        std::cout << "THREAD FINISHED" << std::endl;
//    });

    char line[50 + 1];
    while (std::cin.getline(line, 50 + 1));
//    boost::asio::post(_context,
//        boost::bind(&chat_client::do_close, this)
//    );

    _thread.join();
//    boost::asio::ip::tcp::endpoint endpoint(
//        boost::asio::ip::address::from_string(_networkInfos.getIp()),
//        _networkInfos.getPort()
//    );
//    _acceptor
}

void Socket::start_accept()
{
//    chat_session_ptr new_session(new chat_session(io_context_, room_));
    _acceptor.async_accept(
        _socket,
        boost::bind(&Socket::handle_accept, this, boost::asio::placeholders::error)
    );
}

void Socket::lol(const std::string &buffer)
{

//    std::cout << "READ" << std::endl;
    if (!buffer.empty())
        std::cout << "READ" << std::endl;
    std::string buff("lolmddr");
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(buff, 4),
        boost::bind(&Socket::lol, this, buff)
    );
}

void Socket::handle_accept(const boost::system::error_code &error)
{
//    std::cout << "START ACCEPT" << std::endl;
    if (!error) {
        std::cout << "ACCEPT OK" << std::endl;
        std::string buffer = std::string("lolmddr");
//        while(1);
//        boost::asio::async_read(
//            _socket,
//            boost::asio::buffer(buffer, 4),
//            boost::bind(&Socket::lol, this, buffer)
////            [buffer] { return lol(buffer); }
////            [this] { std::cout << "READ" << std::endl;}
////            boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
//        );

//        session->start_session();
    }
//    std::cout << "RESTART START ACCEPT" << std::endl;
    start_accept();
}

void BabelServer::Socket::stop()
{
    std::cout << "BABEL SOCKET STOP" << std::endl;
    _context.stop();
//    _thread.join();
}

void Socket::setSocketOptions()
{
    boost::asio::socket_base::reuse_address option(true);
    _acceptor.set_option(option);
}

void Socket::setSignalsHandeled()
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
    _signals.async_wait(boost::bind(&Socket::stop, this));
//    _signals.async_wait([this] { stop(); });
}