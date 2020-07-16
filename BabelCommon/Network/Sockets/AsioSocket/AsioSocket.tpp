/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/16/20).
** File description:
** [AsioSocket.hpp]: Header file for AsioSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOSOCKET_TPP
#define CPP_BABEL_2020_ASIOSOCKET_TPP

#include <boost/asio.hpp>
#include "ASocket.hpp"
#include "NetworkInfos.hpp"
#include "BoostThread.hpp"

#include <iostream>

namespace BabelNetwork {
    /* <- Asio Listener Structure -> */
    using AsioListener = struct Listener {
        Listener(boost::asio::io_context &context, boost::asio::ip::tcp::acceptor acceptor);

        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::signal_set _signals;
    };

    AsioListener::Listener(boost::asio::io_context &context, boost::asio::ip::tcp::acceptor acceptor)
        : _acceptor(std::move(acceptor)), _signals(context) {};

    template<class T>
    class AsioSocket : virtual public ASocket {


        /* <- Constructor - Destructor -> */
    public:
        explicit AsioSocket(boost::asio::io_context &context)
            : _context(context) {};


        /* <- Public Methods -> */
    public:
        [[nodiscard]] boost::asio::io_context &getContext() const
        {
            return _context;
        }

        void stop() override
        {
            _context.stop();
        };

        /* <- Private Methods -> */
    private:

        /* <- Attributes -> */
    protected:
        boost::asio::io_context &_context;
        T _handler;
    };

/* ------------------------------------------------------------ */

    template<>
    class AsioSocket<boost::asio::ip::tcp::socket> : virtual public ASocket {
        /* <- Constructor - Destructor -> */
    public:
        AsioSocket(boost::asio::io_context &context, const NetworkInfos &nwInfos)
            : ASocket(nwInfos),
              _context(context), _handler(context) {};

        /* <- Public Methods -> */
    public:
        [[nodiscard]] const boost::asio::ip::tcp::socket &getSocket() const
        {
            return _handler;
        }

        /* <- Private Methods -> */
    private:

//        [[nodiscard]] virtual bool sendResponse(const AResponse &response) = 0;

        /* <- Attributes -> */
    protected:
        boost::asio::io_context &_context;
        boost::asio::ip::tcp::socket _handler;
    };

/* ------------------------------------------------------------ */

    template<>
    class AsioSocket<AsioListener> : virtual public ASocket {
    public:
        AsioSocket(boost::asio::io_context &context, const NetworkInfos &nwInfos)
            : ASocket(nwInfos),
              _context(context),
              _handler(context, boost::asio::ip::tcp::acceptor(
                  _context,
                  boost::asio::ip::tcp::endpoint(
                      boost::asio::ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()
                  ))
              )
        {
        }
        /* <- Public Methods -> */
    public:
        [[nodiscard]] boost::asio::ip::tcp::acceptor &getAcceptor() { return _handler._acceptor; }

        [[nodiscard]] boost::asio::signal_set &getSignals() { return _handler._signals; }

        [[nodiscard]] bool sendResponse(const AResponse &response) final
        {
            std::cerr << "Listener cannot send responses" << std::endl;
            return false;
        };

        void stop() final
        {
            std::cout << "LISTENER STOPPED" << std::endl;
            _context.stop();
        };


        /* <- Private Methods -> */
    private:

        /* <- Attributes -> */
    protected:
        boost::asio::io_context &_context;
        AsioListener _handler;
    };
}

#endif /* CPP_BABEL_2020_ASIOSOCKET_TPP */
