/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioListener.cpp]: Source file for AsioListener feature.
*/

#include "AsioListener.hpp"

using namespace BabelServer;

AsioListener::AsioListener(const BabelNetwork::NetworkInfos &networkInfos, io_context &context)
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
            std::cout << "THREAD LAUNCHED on "<< _networkInfos << std::endl;
            _context.run();
            std::cout << "THREAD FINISHED on "<< _networkInfos << std::endl;
        }
        )
    );
}

AsioListener::~AsioListener()
{
    stop();
}

void AsioListener::start()
{
    std::cout << "START / RESTART" << std::endl;
    boost::shared_ptr<BabelNetwork::AsioClientSocket> new_session(
        new BabelNetwork::AsioClientSocket(_networkInfos, _context));
    _acceptor.async_accept(
        new_session->getSocket(),
        boost::bind(&AsioListener::handle_accept, this, new_session, boost::asio::placeholders::error)
    );
}

void AsioListener::stop()
{
    std::cout << "LISTENER STOPPED" << std::endl;
    _context.stop();
}

[[nodiscard]] bool AsioListener::sendResponse(const BabelNetwork::AResponse &response)
{
    std::cerr << "Listener cannot send response" << response << std::endl;
    return false;
}

void AsioListener::handle_accept(const boost::shared_ptr<BabelNetwork::AsioClientSocket> &session,
    const boost::system::error_code &error)
{
    if (!error) {
        std::cout << "ACCEPT OK" << std::endl;
        session->start();
    }
    start();
}

void AsioListener::setSignalsHandeled()
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
    _signals.async_wait(boost::bind(&BabelNetwork::AsioSocket::stop, this));
}


