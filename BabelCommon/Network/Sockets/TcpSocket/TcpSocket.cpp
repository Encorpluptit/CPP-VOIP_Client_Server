/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [TcpSocket.cpp]: Source file for TcpSocket feature.
*/

#include "TcpSocket.hpp"

using namespace BabelNetwork;

TcpSocket::TcpSocket()
    : _new_context(std::make_unique<boost::asio::io_context>()),
      _io_context(*_new_context),
      _socket(_io_context) {}

TcpSocket::TcpSocket(boost::asio::io_context &io_context)
    : _new_context(nullptr), _io_context(io_context), _socket(io_context) {}

void TcpSocket::disconnect()
{
    _connected = false;
    _socket.close();
}

bool TcpSocket::connect(const NetworkInfos &networkInfos)
{
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address::from_string(networkInfos.getIp()), networkInfos.getPort()
    );
    _socket.connect(endpoint);
    //    start();
    return false;
}

bool TcpSocket::isAvailable() const
{
    return _socket.available();
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

//
//void	TCPSocket::start(void) {
//    _socket.non_blocking(true);
//    this->_isConnected = true;
//    ::boost::asio::ip::tcp::no_delay nod_option(true);
//    ::boost::asio::socket_base::send_buffer_size sbs_option(32768 * 4);
//
//    _socket.set_option(nod_option);
//    _socket.set_option(sbs_option);
//    _socket.async_receive(::boost::asio::null_buffers(),
//        ::boost::bind(&TCPSocket::_onReceiveHandler, this,
//            ::boost::asio::placeholders::error));
//}

//void	TCPSocket::connect(std::string const &host, std::uint16_t port) {
//    ::boost::asio::ip::tcp::endpoint endpoint(::boost::asio::ip::address::from_string(host), port);
//
//    _socket.connect(endpoint);
//    start();
//}
//
//void TCPSocket::disconnect(void) {
//    _isConnected = false;
//    _socket.close();
//}
//
//void	TCPSocket::_onReceiveHandler(::boost::system::error_code const &e) {
//    auto	len = _socket.available();
//
//    if (!e && len) {
//        _hdl.operator()(len);
//    } else if ((::boost::asio::error::eof == e)
//        || (::boost::asio::error::connection_reset == e)
//        || (e)
//        || (!len)) {
//        this->_isConnected = false;
//        if (_onDisconnect != nullptr)
//            _onDisconnect();
//        return;
//    }
//    _socket.async_receive(::boost::asio::null_buffers(),
//        ::boost::bind(&TCPSocket::_onReceiveHandler, this,
//            ::boost::asio::placeholders::error));
//}
//
//std::size_t	TCPSocket::send(std::uint8_t *buff, std::size_t len) {
//    auto ret = _socket.send(
//        ::boost::asio::buffer(buff, len));
//    return ret;
//}
//
//std::size_t	TCPSocket::receive(std::uint8_t *buff, std::size_t len) {
//    return	_socket.read_some(::boost::asio::buffer(buff, len));
//}
//
//std::size_t	TCPSocket::available(void) const {
//    return _socket.available();
//}
//
//}
//}
