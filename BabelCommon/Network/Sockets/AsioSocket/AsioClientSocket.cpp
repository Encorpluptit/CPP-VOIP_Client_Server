/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioClientSocket.cpp]: Source file for AsioClientSocket feature.
*/

#include "AsioClientSocket.hpp"

using namespace BabelNetwork;

AsioClientSocket::AsioClientSocket(const BabelNetwork::NetworkInfos &networkInfos, io_context &context)
    : BabelNetwork::AsioSocket(networkInfos, context),
      _socket(_context)
{

}

void AsioClientSocket::start()
{
    std::cout << "START SESSION" << std::endl;
    boost::asio::async_read(
        _socket,
        boost::asio::buffer(&_hdr, BabelNetwork::AResponse::getHeaderSize()),
        boost::bind(&AsioClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
    );
}

bool AsioClientSocket::sendResponse(const BabelNetwork::AResponse &response)
{
    std::cout << "START DELIVER" << std::endl;

    boost::asio::post(
        _context,
        boost::bind(&AsioClientSocket::do_write, shared_from_this(), boost::ref(response))
    );
    return true;
}

void AsioClientSocket::connect()
{
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
        std::cout << "HANDLE CONNECT (DO FCT TO LAUNCH SOCKET)" << std::endl;
        boost::asio::async_read(
            getSocket(),
            boost::asio::buffer(&_hdr, AResponse::getHeaderSize()),
            boost::bind(&AsioClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        std::cout << "Socket Cannot connect" << std::endl;
    }
}

void AsioClientSocket::handle_read_header(const boost::system::error_code &error)
{
    _read_msg = BabelNetwork::AResponse::getResponse(_hdr);

    if (!_read_msg) {
        std::cout << "Read msg null" << std::endl;
        std::cout << _hdr.responseType << std::endl;
        std::cout << _hdr.returnCode << std::endl;
        return;
    }
    if (!error && _read_msg && _read_msg->decode_header()) {
//    if (!error ) {
        std::cout << "START READ HEADER" << std::endl;
//        if (!_read_msg || !_read_msg->decode_header()) {
//            std::cout << "error in read header" << _read_msg << "|" << _read_msg->getResponseType() << std::endl;
//            return;
//        }
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_read_msg->getBodyData(), _read_msg->getHeaderDataLength()),
            boost::bind(&AsioClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        std::cerr << "ERROR IN HANDLE READ HEADER (close here ?)" << std::endl;
//        if (error.category() == )
//        if (error.value())
        //TODO: Throw error to differenciate between server use and client use ?

//                stop();
//            room_.leave(shared_from_this());
    }
}

void AsioClientSocket::handle_read_body(const boost::system::error_code &error)
{
    if (!error && _read_msg->decode_data()) {
        std::cout << "START READ BODY" << std::endl;
        std::cout << "DATA = " << _read_msg->getBodyData() << std::endl;
        _read_queue.push(_read_msg);
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(&_hdr, BabelNetwork::AResponse::getHeaderSize()),
            boost::bind(&AsioClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
        );
    } else {
        std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
        stop();
    }
}

void AsioClientSocket::do_write(const BabelNetwork::AResponse &response)
{
    bool write_in_progress = !_write_queue.empty() ;
    std ::cout << "do write" << std::endl;

    _write_queue.push(response.getResponse());
//    if (!write_in_progress && _write_queue.front()->encode_header()) {
    if (!write_in_progress) {
        std ::cout << "ici" << std::endl;
        _write_queue.front()->encode_header();
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(_write_queue.front()->getHeaderData(), _write_queue.front()->getHeaderSize()),
            boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
        );
    }
//    if (!_write_queue.empty() && _write_queue.front()->encode_header()) {
//
//        std::cout << "Writing response in do write" << std::endl;
//        boost::asio::async_write(
//            _socket,
//            boost::asio::buffer(_write_queue.front()->getHeaderData(), _write_queue.front()->getHeaderSize()),
//            boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
//        );
//    }
//    std::cout << "ICI" << std::endl;
}

void AsioClientSocket::handle_write(const boost::system::error_code &error)
{
    std ::cout << "handle write" << std::endl;
    if (!error) {
        _write_queue.pop();
        if (!_write_queue.empty() && _write_queue.front()->encode_header()) {
            boost::asio::async_write(
                _socket,
                boost::asio::buffer(_write_queue.front()->getHeaderData(), _write_queue.front()->getHeaderSize()),
                boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
        }
    } else {
//        do_close();
    }

//    if (!error) {
//        std::cout << "Writing response in handle write" << std::endl;
////        boost::asio::async_write(
////            _socket,
////            boost::asio::buffer(_write_queue.front().data(), write_msgs_.front().length()),
////            boost::bind(&chat_client::handle_write, this, boost::asio::placeholders::error)
////        );
//    } else {
//        std::cerr << "ERROR IN HANDLE WRITE" << std::endl;
//    }
}

