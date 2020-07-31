/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/27/20).
** File description:
** [AsioClientSocket.hpp]: Header file for AsioClientSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP
#define CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP

#include "AsioSocket.hpp"

namespace BabelNetwork {
    using namespace boost::asio;

    class AsioClientSocket final : public boost::enable_shared_from_this<AsioClientSocket>, public AsioSocket {
        /* <- Constructor - Destructor -> */
    public:
        explicit AsioClientSocket(const BabelNetwork::NetworkInfos &networkInfos, io_context &context);

        /* <- Public Methods -> */
    public:

        void start() final;

        bool sendResponse(const BabelNetwork::AResponse &response) final;

        void connect();


        /* <- Private Methods -> */
    private:

        void handle_connect(const boost::system::error_code &error);

        void handle_read_header(const boost::system::error_code &error);

        void handle_read_body(const boost::system::error_code &error);

        void do_write(const BabelNetwork::AResponse &response);

        void handle_write(const boost::system::error_code &error);


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
    };

}

#endif /* CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP */
