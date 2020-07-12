/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [TcpSocket.hpp]: Header file for TcpSocket feature.
*/

#ifndef CPP_BABEL_2020_TCPSOCKET_HPP
#define CPP_BABEL_2020_TCPSOCKET_HPP

#include <memory>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ASocket.hpp"

namespace BabelNetwork {

    class TcpSocket final : virtual public ASocket, public boost::enable_shared_from_this<TcpSocket> {
        /* <- Constructor - Destructor -> */
    public:
        TcpSocket();
        explicit TcpSocket(boost::asio::io_context &io_context);
        ~TcpSocket() final = default;

        /* <- Methods -> */
    public:
        [[nodiscard]] bool connect(const NetworkInfos &networkInfos) final;

        void disconnect() final;

        [[nodiscard]] bool isAvailable() const final ;

        /* <- Getters / Setters -> */
    public:
        const boost::asio::ip::tcp::socket &getSocket() const;

        const boost::asio::io_context &getIoContext() const;

        /* <- Attributes -> */
    private:
        std::unique_ptr<boost::asio::io_context> _new_context;
        boost::asio::io_context &_io_context;
        boost::asio::ip::tcp::socket _socket;
    };

}

#endif /* CPP_BABEL_2020_TCPSOCKET_HPP */
