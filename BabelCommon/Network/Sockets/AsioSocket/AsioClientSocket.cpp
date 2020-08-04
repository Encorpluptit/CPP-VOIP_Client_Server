/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioClientSocket.cpp]: Source file for AsioClientSocket feature.
*/

#include <iostream>
#include "AsioClientSocket.hpp"

using namespace BabelNetwork;

AsioClientSocket::AsioClientSocket(
    const std::string &address,
    const std::string &port, io_context &context,
    SocketHandler handlerType,
    BabelUtils::Logger &logger
)
    : BabelNetwork::ASocket(address, port, logger),
      _context(context),
      _socket(_context),
      _handler(handlerType)
{

}

AsioClientSocket::~AsioClientSocket()
{
    _socket.close();
//    _read_msg.reset();
//    while (!_read_queue.empty())
//        _read_queue.pop();
//    while (!_write_queue.empty())
//        _write_queue.pop();
//    _socket.close();
}

void AsioClientSocket::start()
{
    std::cout << "START SESSION" << std::endl;
    _logger.logThis("START SESSION");
    handle_read_header();
}

bool AsioClientSocket::sendResponse(const BabelNetwork::AResponse &response)
{
    _logger.logThis("Starting to deliver response :", response);
    boost::asio::post(
        _context,
        boost::bind(&AsioClientSocket::do_write, shared_from_this(), boost::ref(response))
    );
    return true;
}

void AsioClientSocket::connect()
{
    _logger.logThis("Trying to connect");
    ip::tcp::resolver resolver(_context);
    _endpoints = resolver.resolve(_networkInfos.getIp(), _networkInfos.getPortStr());
    boost::asio::async_connect(
        _socket,
        _endpoints,
        boost::bind(&AsioClientSocket::handle_connect, shared_from_this(), boost::asio::placeholders::error)
    );
}

void AsioClientSocket::handle_connect(const boost::system::error_code &error)
{
    if (!error) {
        setReady();
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(&_hdr, AResponse::getHeaderSize()),
            boost::bind(&AsioClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        _logger.logThis("Socket Cannot connect");
        std::cerr << "Socket Cannot connect" << std::endl;
    }
}

void AsioClientSocket::handle_read_header()
{
    memset(&_hdr, 0, BabelNetwork::AResponse::getHeaderSize());
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(&_hdr, BabelNetwork::AResponse::getHeaderSize()),
        boost::bind(&AsioClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
    );
}

void AsioClientSocket::handle_read_body(const boost::system::error_code &error)
{
    _read_msg = BabelNetwork::AResponse::getResponse(_hdr);

    if (!error) {
        if (!_read_msg) {
            _logger.logThis(
                "Read msg null \ncode : %d, type %d, sz: %u",
                _hdr.code, _hdr.responseType, _hdr.bodySize
            );
            return;
        }
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_read_msg->getBody(), _hdr.bodySize),
            boost::bind(&AsioClientSocket::finish_read_body, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        std::cerr << "ERROR IN HANDLE READ BODY : " + error.message() << std::endl;
        if (getHandler() == SocketHandler::Client) {
            _logger.logThis("Client Stopped" + error.message());
            stop();
        } else {
            _logger.logThis("ERROR IN HANDLE READ BODY BY SERVER - Client disconnected : " + error.message());
            std::cerr << "Throw Exeption ?" << std::endl;
        }
    }
}

void AsioClientSocket::finish_read_body(const boost::system::error_code &error)
{
    if (!error && _read_msg->decode_data()) {
        std::cout << "BODY READ -- DATA = " << _read_msg->serialize_data() << std::endl;
        _read_queue.push(_read_msg);
        _logger.logThis(*_read_msg);
        handle_read_header();
    } else {
        _logger.logThis("ERROR IN FINISH READ BODY" + error.message());
        std::cerr << "ERROR IN FINISH READ BODY" << std::endl;
        if (getHandler() == SocketHandler::Client) {
            stop();
        } else {
            std::cerr << "Throw Exeption ?" << std::endl;
        }
    }
}

void AsioClientSocket::do_write(const BabelNetwork::AResponse &response)
{
    bool write_in_progress = !_write_queue.empty();
//    std::cout << "do write" << std::endl;

    _write_queue.push(response.getResponse());
    if (!write_in_progress && _write_queue.front()->encode()) {
        _logger.logThis("Sending Response = ", response);
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(_write_queue.front()->getDataByte(), _write_queue.front()->getResponseSize()),
            boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
        );
    }
}

void AsioClientSocket::handle_write(const boost::system::error_code &error)
{
//    std::cout << "handle write" << std::endl;
    if (!error) {
//        std::cout << "handle write OK" << std::endl;
        _write_queue.pop();
        if (!_write_queue.empty() && _write_queue.front()->encode()) {
            _logger.logThis("2 or more messages to send  - Sending Response = ", *_write_queue.front());
            boost::asio::async_write(
                _socket,
                boost::asio::buffer(_write_queue.front()->getDataByte(), _write_queue.front()->getResponseSize()),
                boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
        }
    } else {
        _logger.logThis("Error in handle write : " + error.message());
//        std::cerr << "handle write NOT OK" << std::endl;
    }
}
