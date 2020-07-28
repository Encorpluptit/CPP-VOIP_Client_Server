/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/16/20).
** File description:
** [AsioSocket.hpp]: Header file for AsioSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOSOCKET_HPP
#define CPP_BABEL_2020_ASIOSOCKET_HPP

#include <iostream>
#include <boost/asio.hpp>
#include "ASocket.hpp"
#include "NetworkInfos.hpp"
#include "BoostThread.hpp"

namespace BabelNetwork {
    using namespace boost::asio;

    class AsioSocket : public ASocket {
        /* <- Constructor - Destructor -> */
    public:
        explicit AsioSocket(const NetworkInfos &networkInfos, io_context &context);

        /* <- Public Methods -> */
    public:
        void stop() override;
//        virtual void handle_read_header(const boost::system::error_code &error) = 0;

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] io_context &getContext() const { return _context; }

        /* <- Attributes -> */
    protected:
        io_context &_context;
    };
}

#endif /* CPP_BABEL_2020_ASIOSOCKET_HPP */
