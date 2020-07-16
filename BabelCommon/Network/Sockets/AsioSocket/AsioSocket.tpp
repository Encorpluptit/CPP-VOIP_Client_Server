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
    using Listener = struct Listener {
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::signal_set _signals;
        BabelUtils::BoostThread _thread;
    };

    template<class T>
    class AsioSocket : virtual public ASocket {


        /* <- Constructor - Destructor -> */
    public:
//        AsioSocket(boost::asio::io_context &context)
//            : _context(context), _handler(context) {};


        /* <- Public Methods -> */
    public:

        /* <- Private Methods -> */
    private:

        /* <- Attributes -> */
    private:
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

        /* <- Methods -> */
    public:

//        [[nodiscard]] virtual bool sendResponse(const AResponse &response) = 0;

        /* <- Attributes -> */
    private:
        boost::asio::io_context &_context;
        boost::asio::ip::tcp::socket _handler;
    };

/* ------------------------------------------------------------ */

//    template<>
//    class AsioSocket<Listener> : virtual public ASocket {
//    public:
//        AsioSocket(boost::asio::io_context &context, const NetworkInfos &nwInfos)
//            : ASocket(nwInfos),
//              _context(context),
//              _acceptor(
//                  boost::asio::ip::tcp::acceptor(
//                      _context,
//                      boost::asio::ip::tcp::endpoint(
//                          boost::asio::ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()
//                      )
//                  )
//              ),
//              _signals(_context),
//              _thread([ObjectPtr = &_context] {
//                      std::cout << "THREAD LAUNCHED" << std::endl;
//                      ObjectPtr->run();
//                      std::cout << "THREAD FINISHED" << std::endl;
//                  }
//              )
//        {
//        }
//        /* <- Attributes -> */
//    private:
//        boost::asio::io_context &_context;
//        boost::asio::ip::tcp::acceptor _acceptor;
//        boost::asio::signal_set _signals;
//        BabelUtils::BoostThread _thread;
//    };
}

#endif /* CPP_BABEL_2020_ASIOSOCKET_TPP */
