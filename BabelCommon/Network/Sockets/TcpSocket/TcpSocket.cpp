/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [TcpSocket.cpp]: Source file for TcpSocket feature.
*/

#include "TcpSocket.hpp"

using namespace BabelNetwork;

TcpSocket::TcpSocket(boost::asio::io_context &io_context)
    : _io_context(io_context), _socket(io_context)
{}

bool TcpSocket::disconnect()
{
    _connected = false;
    _socket.close();
}

bool TcpSocket::connect()
{
    return false;
}

bool TcpSocket::isAvailable() const
{
    return false;
}

const boost::asio::ip::tcp::socket &TcpSocket::getSocket() const
{
    return _socket;
}

const boost::asio::io_context &TcpSocket::getIoContext() const
{
    return _io_context;
}

//TCPSocket::TCPSocket():
//    _ios(new ::boost::asio::io_service()),
//    _socket(*_ios),
//    _localIos(true) {}
//
//TCPSocket::TCPSocket(::boost::asio::io_service &ios):
//    _ios(&ios),
//    _socket(*_ios),
//    _localIos(false) {}
//
