/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioClientSocket.cpp]: Source file for AsioClientSocket feature.
*/

#include <iostream>
#include "AsioClientSocket.hpp"
#include "ClientError.hpp"
#include "Debug.hpp"

using namespace BabelNetwork;

AsioClientSocket::AsioClientSocket(
    const std::string &address,
    const std::string &port,
    BabelUtils::Logger &logger,
    io_context &context,
    SocketHandler handlerType
)
    : ClientSocket(address, port, logger),
      _context(context),
      _socket(_context),
      _handler(handlerType)
{

}

AsioClientSocket::~AsioClientSocket()
{
//    _socket.close();
    if (_thread)
        _thread->stop();
}

void AsioClientSocket::start()
{
    dbg("%s", "START SESSION")
    _logger.logThis("START SESSION");
    read_header();
}

bool AsioClientSocket::sendResponse(const BabelNetwork::AResponse &response)
{
    bool write_in_progress = !_write_queue.empty();

    _logger.logThis(response, "Queue response :");
    _write_queue.push(response.get_shared_from_this());
    boost::asio::post(
        _context,
        boost::bind(&AsioClientSocket::do_write, shared_from_this(), write_in_progress)
    );
    return true;
}

void AsioClientSocket::connect()
{
    _logger.logThis(_networkInfos, "Trying to connect");
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
        _logger.logThis(describe());
        read_header();
    } else {
        _logger.logThis("Socket Cannot connect");
        std::cerr << "Socket Cannot connect" << std::endl;
    }
}

void AsioClientSocket::read_header()
{
    using namespace BabelNetwork;

    memset(_headerBuffer, 0, AResponse::HeaderSize);
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(_headerBuffer, AResponse::HeaderSize),
        boost::bind(&AsioClientSocket::read_data_infos, shared_from_this(), boost::asio::placeholders::error)
    );
}

void AsioClientSocket::read_data_infos(const boost::system::error_code &error)
{
    _read_msg = BabelNetwork::AResponse::getResponse(_headerBuffer);

    if (!error) {
        if (!_read_msg) {
            AResponse::ResponseHeader _hdr{};
            memcpy(&_hdr, _headerBuffer, AResponse::HeaderSize);
            _logger.logThis(
                "Read msg null \ncode : %d, type %d, sz: %u",
                _hdr._code, _hdr._responseType, _hdr._dataInfosSize
            );
            return;
        }
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_read_msg->getDataByteDataInfos(), _read_msg->getDataInfosSize()),
            boost::bind(&AsioClientSocket::read_data, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        handle_error("{ read_data_infos } : ", error);
    }
}

void AsioClientSocket::read_data(const boost::system::error_code &error)
{
    if (!error) {
        if (!_read_msg->decode_data_infos()) {
            _logger.logThis("ERROR IN HANDLE READ DAT INFOS : Decode failed");
            return;
        }
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_read_msg->getDataByteBody(), _read_msg->getDataSize()),
            boost::bind(&AsioClientSocket::queue_read_response, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        handle_error("{ queue_read_response } : ", error);
    }
}

void AsioClientSocket::queue_read_response(const boost::system::error_code &error)
{
    if (!error && _read_msg->decode_data()) {
        std::cout << "BODY READ -- DATA = " << _read_msg->serialize_data() << std::endl;
        _read_queue.push(_read_msg);
        _logger.logThis(*_read_msg);
        read_header();
    } else {
        handle_error("{ read_data } : ", error);
    }
}

void AsioClientSocket::do_write(bool write_in_progress)
{
    if (!write_in_progress && _write_queue.front()->encode()) {
        _logger.logThis(*_write_queue.front(), "Sending Response = ");
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(_write_queue.front()->getDataByte(), _write_queue.front()->getResponseSize()),
            boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
        );
    }
}

void AsioClientSocket::handle_write(const boost::system::error_code &error)
{
    if (!error) {
        _write_queue.pop();
        if (!_write_queue.empty() && _write_queue.front()->encode()) {
            boost::asio::async_write(
                _socket,
                boost::asio::buffer(_write_queue.front()->getDataByte(), _write_queue.front()->getResponseSize()),
                boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
        }
    } else {
        handle_error("{ handle write } : ", error);
        _logger.logThis("Error in handle write : " + error.message());
    }
}

std::string AsioClientSocket::describe()
{
    return BabelUtils::format(
        "Local connexion from %s with port %u to %s with port %u",
        _socket.local_endpoint().address().to_string().c_str(),
        _socket.local_endpoint().port(),
        _socket.remote_endpoint().address().to_string().c_str(),
        _socket.remote_endpoint().port()
    );
}

void AsioClientSocket::handle_error(const std::string &msg, const boost::system::error_code &error)
{
    if (getHandler() == SocketHandler::Client) {
        auto errorMsg = msg + error.message();
        if (error == boost::asio::error::eof) {
            _logger.logThis(errorMsg + " ==> Connection closed by server.");
        } else {
            _logger.logThis("Error : " + errorMsg);
        }
        stop();
        throw BabelErrors::ClientError(errorMsg, *this);
    } else {
        // TODO: Destroy properly client in Listener and remove from queue
        auto errorMsg = msg + " (Client Connection Stopped) : " + error.message() + +"\n" + describe();
        _logger.logThis(errorMsg);
        throw BabelErrors::ClientError(errorMsg, *this);
    }
}
