/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioListenerSocket.cpp]: Source file for AsioListenerSocket feature.
*/

#include "AsioListenerSocket.hpp"

using namespace BabelServer;

AsioListenerSocket::AsioListenerSocket(const BabelNetwork::NetworkInfos &networkInfos, io_context &context)
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
}

AsioListenerSocket::~AsioListenerSocket()
{
    stop();
}

void AsioListenerSocket::start()
{
    std::cout << "START / RESTART" << std::endl;
    boost::shared_ptr<BabelNetwork::AsioClientSocket> new_session(
        new BabelNetwork::AsioClientSocket(_networkInfos, _context));
    _acceptor.async_accept(
        new_session->getSocket(),
        boost::bind(&AsioListenerSocket::handle_accept, this, new_session, boost::asio::placeholders::error)
    );
}

void AsioListenerSocket::stop()
{
    std::cout << "LISTENER STOPPED" << std::endl;
    _context.stop();
}

[[nodiscard]] bool AsioListenerSocket::sendResponse(const BabelNetwork::AResponse &response)
{
    std::cerr << "Listener cannot send response" << response << std::endl;
    return false;
}

void AsioListenerSocket::handle_accept(const boost::shared_ptr<BabelNetwork::AsioClientSocket> &session,
    const boost::system::error_code &error)
{
    if (!error) {
        std::cout << "ACCEPT OK" << std::endl;
        session->start();
    }
    start();
}

void AsioListenerSocket::setSignalsHandeled()
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
    _signals.async_wait(boost::bind(&BabelNetwork::AsioSocket::stop, this));
}


