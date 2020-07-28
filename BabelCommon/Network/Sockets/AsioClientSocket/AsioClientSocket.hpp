/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/27/20).
** File description:
** [AsioClientSocket.hpp]: Header file for AsioClientSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP
#define CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP

#include <queue>
#include "AsioSocket.hpp"

namespace BabelNetwork {
    using namespace boost::asio;

    class AsioClientSocket final : public boost::enable_shared_from_this<AsioClientSocket>, public AsioSocket {
        /* <- Constructor - Destructor -> */
    public:
        explicit AsioClientSocket(const BabelNetwork::NetworkInfos &networkInfos, io_context &context)
            : BabelNetwork::AsioSocket(networkInfos, context),
              _socket(_context)
        {

        }

        /* <- Public Methods -> */
    public:

        void start() final
        {
            std::cout << "START SESSION" << std::endl;
            boost::asio::async_read(
                getSocket(),
                boost::asio::buffer(_data, DATALENGTH),
                boost::bind(&AsioClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
            );
        }

        bool sendResponse(const BabelNetwork::AResponse &response) final
        {
            std::cout << "START DELIVER" << std::endl;
            boost::asio::async_write(
                getSocket(),
                boost::asio::buffer(_msg.c_str(), _msg.length()),
                boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
            return true;
        }

        void connect()
        {
            ip::tcp::resolver resolver(_context);
            _endpoints = resolver.resolve(_networkInfos.getIp(), _networkInfos.getPortStr());
            boost::asio::async_connect(
                _socket,
                _endpoints,
                boost::bind(&AsioClientSocket::handle_connect, this, boost::asio::placeholders::error)
            );
        }


        /* <- Private Methods -> */
    private:

        void handle_connect(const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "HANDLE CONNECT (DO FCT TO LAUNCH SOCKET)" << std::endl;
//                boost::asio::async_read(_socket,
//                    boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//                    boost::bind(&chat_client::handle_read_header, this, boost::asio::placeholders::error)
//                );
            }
        }

        void handle_read_header(const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "START READ HEADER" << std::endl;
                std::cout << "Data before :" << _data << std::endl;
                boost::asio::async_read(
                    getSocket(),
                    boost::asio::buffer(&_hdr, BabelNetwork::AResponse::getResponseHeaderSize()),
                    boost::bind(&AsioClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
                );
                std::cout << "Data After :" << _data << std::endl;
            } else {
                std::cerr << "ERROR IN HANDLE READ HEADER (close here ?)" << std::endl;
                stop();
//            room_.leave(shared_from_this());
            }
//        if (!error && read_msg_.decode_header()) {
//            std::cout << "START READ HEADER" << std::endl;
//            boost::asio::async_read(socket_,
//                boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//                boost::bind(&ClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
//            );
//        } else {
//            room_.leave(shared_from_this());
//        }
        }

        void handle_read_body(const boost::system::error_code &error)
        {
            auto new_msg = BabelNetwork::AResponse::getResponse(&_hdr, nullptr);

            if (!error && new_msg->decode_header()) {
                std::cout << "START READ BODY" << std::endl;
                std::cout << "Data before :" << _data << std::endl;
                _responses.push(new_msg);
                boost::asio::async_read(getSocket(),
                    boost::asio::buffer(_data, DATALENGTH),
                    boost::bind(&AsioClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
                );
                std::cout << "Data After :" << _data << std::endl;
            } else {
                std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
                stop();
            }
//        if (!error) {
//            std::cout << "START READ BODY" << std::endl;
//            boost::asio::async_read(
//                socket_,
//                boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//                boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
//            );
//        } else {
//            std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
//            room_.leave(shared_from_this());
//        }
        }

        void handle_write(const boost::system::error_code &error)
        {
            if (!error) {
                boost::asio::async_write(
                    getSocket(),
                    boost::asio::buffer(_msg.c_str(), _msg.length()),
                    boost::bind(&AsioClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
                );
            } else {
                std::cerr << "ERROR IN HANDLE WRITE" << std::endl;
            }
        }


        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] ip::tcp::socket &getSocket()
        {
            return _socket;
        }

        /* <- Attributes -> */
    private:
        ip::tcp::socket _socket;
        ip::tcp::resolver::results_type _endpoints;
        BabelNetwork::AResponse::ResponseHeader _hdr{};
        std::queue <std::shared_ptr<BabelNetwork::IResponse>> _responses;
        std::string _msg;
        static const size_t DATALENGTH = 3;
        char _data[DATALENGTH] = {0};
    };

}

#endif /* CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP */
