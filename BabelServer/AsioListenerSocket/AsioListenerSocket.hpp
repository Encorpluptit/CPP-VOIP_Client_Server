/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/27/20).
** File description:
** [AsioListenerSocket.hpp]: Header file for AsioListenerSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOLISTENERSOCKET_HPP
#define CPP_BABEL_2020_ASIOLISTENERSOCKET_HPP

#include "AsioClientSocket.hpp"

namespace BabelServer {
    using namespace boost::asio;

    class AsioListenerSocket final : public BabelNetwork::AsioSocket {

        /* <- Constructor - Destructor -> */
    public:
        explicit AsioListenerSocket(const BabelNetwork::NetworkInfos &networkInfos, io_context &context)
            : BabelNetwork::AsioSocket(networkInfos, context),
            _endpoint(ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()),
            _acceptor(_context, _endpoint),
            _signals(_context)
            {
                setReady();
                setSignalsHandeled();
                start();
                setThread(boost::make_shared<BabelUtils::BoostThread>(
                    [this] {
                        std::cout << "THREAD LAUNCHED" << std::endl;
                        _context.run();
                        std::cout << "THREAD FINISHED" << std::endl;
                    }
                    )
                );
            };

        ~AsioListenerSocket() final
        {
            stop();
        }

        /* <- Public Methods -> */
    public:
        void start() final
        {
            std::cout << "START / RESTART" << std::endl;
            boost::shared_ptr<BabelNetwork::AsioClientSocket> new_session(
                new BabelNetwork::AsioClientSocket(getNetworkInfos(), _context));
            _acceptor.async_accept(
                new_session->getSocket(),
                boost::bind(&AsioListenerSocket::handle_accept, this, new_session, boost::asio::placeholders::error)
            );
        };

        void stop() final
        {
            std::cout << "LISTENER STOPPED" << std::endl;
            _context.stop();
        };

        [[nodiscard]] bool sendResponse(__attribute__((unused))const BabelNetwork::AResponse &response) final
        {
            std::cerr << "Listener cannot send response" << response << std::endl;
            return false;
        };

        /* <- Private Methods -> */
    private:

        void handle_accept(const boost::shared_ptr<BabelNetwork::AsioClientSocket> &session, const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "ACCEPT OK" << std::endl;
                session->start();
            }
            start();
        }

        void setSignalsHandeled()
        {
            _signals.add(SIGINT);
            _signals.add(SIGTERM);
            _signals.async_wait(boost::bind(&BabelNetwork::AsioSocket::stop, this));
        }

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

#endif /* CPP_BABEL_2020_ASIOLISTENERSOCKET_HPP */
