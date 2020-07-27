/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/16/20).
** File description:
** [Listener.hpp]: Header file for ServerListener feature.
*/

#ifndef CPP_BABEL_2020_SERVERLISTENER_HPP
#define CPP_BABEL_2020_SERVERLISTENER_HPP

#include "Client.tpp"

namespace BabelServer {
    class Listener final : virtual public BabelNetwork::AsioSocket<BabelNetwork::Listener> {
    public:
        explicit Listener(boost::asio::io_context &context, const BabelNetwork::NetworkInfos &nwInfos)
            : ASocket(nwInfos), AsioSocket<BabelNetwork::AsioListener>(context, nwInfos)
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
        }

        ~Listener() final
        {
            stop();
        }

        /* <- Methods -> */
    public:
        void start() final
        {
            std::cout << "START / RESTART" << std::endl;
            boost::shared_ptr<ClientSocket> new_session(
                new ClientSocket(AsioSocket<BabelNetwork::AsioListener>::getContext(), getNetworkInfos(), "msg"));
            getAcceptor().async_accept(
                new_session->getSocket(),
                boost::bind(&BabelServer::Listener::handle_accept, this, new_session, boost::asio::placeholders::error)
            );
        };

        void handle_accept(const boost::shared_ptr<ClientSocket> &session, const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "ACCEPT OK" << std::endl;
                session->start();
            }
            start();
        }

        void setSignalsHandeled()
        {
            getSignals().add(SIGINT);
            getSignals().add(SIGTERM);
            getSignals().async_wait(boost::bind(&Listener::stop, this));
        }
    };
}

#endif /* CPP_BABEL_2020_SERVERLISTENER_HPP */
