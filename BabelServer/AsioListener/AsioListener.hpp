/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/27/20).
** File description:
** [AsioListener.hpp]: Header file for AsioListener feature.
*/

#ifndef CPP_BABEL_2020_ASIOLISTENER_HPP
#define CPP_BABEL_2020_ASIOLISTENER_HPP

#include "AsioClientSocket.hpp"

namespace BabelServer {
    using namespace boost::asio;

    class AsioListener final : public BabelNetwork::AsioSocket {

        /* <- Constructor - Destructor -> */
    public:
        explicit AsioListener(
            const std::string &address,
            const std::string &port,
            io_context &context
        );

        ~AsioListener() final;

        /* <- Public Methods -> */
    public:
        void start() final;

        void stop() final;

        [[nodiscard]] bool sendResponse(__attribute__((unused))const BabelNetwork::AResponse &response) final;

        /* <- Private Methods -> */
    private:

        void handle_accept(
            const boost::shared_ptr<BabelNetwork::AsioClientSocket> &session,
            const boost::system::error_code &error
        );

        void setSignalsHandeled();

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const ip::tcp::endpoint &getEndpoint() const
        {
            return _endpoint;
        }

        [[nodiscard]] const ip::tcp::acceptor &getAcceptor() const
        {
            return _acceptor;
        }

        [[nodiscard]] const signal_set &getSignals() const
        {
            return _signals;
        }

        /* <- Attributes -> */
    private:
        ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::signal_set _signals;
    };

}

#endif /* CPP_BABEL_2020_ASIOLISTENER_HPP */
