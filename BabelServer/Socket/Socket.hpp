/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/13/20).
** File description:
** [Socket.hpp]: Header file for Socket feature.
*/

#ifndef CPP_BABEL_2020_SOCKET_HPP
#define CPP_BABEL_2020_SOCKET_HPP

#include <list>
#include <memory>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include "ASocket.hpp"
#include "AResponse.hpp"
#include "BoostThread.hpp"

namespace BabelServer {
    class Socket final : virtual public BabelNetwork::ASocket {
    public:
        explicit Socket(const BabelNetwork::NetworkInfos &networkInfos);

    public:
        void launch() final;

        void stop() final;

        void start_accept();

        void handle_accept(const boost::system::error_code &error);

        void lol(const std::string &buffer);

    private:
        void setSocketOptions();

        void setSignalsHandeled();

        /* <- Attributes -> */
    private:
        boost::asio::io_context _context;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::signal_set _signals;
        BabelUtils::BoostThread _thread;
        std::deque<std::unique_ptr<BabelNetwork::AResponse>> _responses;
    };

}

#endif /* CPP_BABEL_2020_SOCKET_HPP */
