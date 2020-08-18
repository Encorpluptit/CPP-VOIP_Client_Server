/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioListener.cpp]: Source file for AsioListener feature.
*/

#include <iostream>
#include "AsioListener.hpp"
#include "Debug.hpp"
#include "ClientError.hpp"

using namespace BabelServer;

AsioListener::AsioListener(const std::string &address, const std::string &port, BabelUtils::Logger &logger)
    : BabelNetwork::ASocket(address, port, logger),
      _endpoint(ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()),
      _acceptor(_context, _endpoint),
      _signals(_context)
{
    setSignalsHandeled();
}

AsioListener::~AsioListener()
{
    if (_thread)
        _thread->stop();
    _asioClients.clear();
}

void AsioListener::start()
{
    std::cout << "START / RESTART" << std::endl;

    auto s = BabelUtils::format("Local connexion from %s with port %u",
        _acceptor.local_endpoint().address().to_string().c_str(),
        _acceptor.local_endpoint().port()
    );
    _logger.logThis(s);
    std::cout << s << std::endl;
    setReady();
    setThread(
        boost::make_shared<BabelUtils::BoostThread>(
            [this] { this->launch_listener(); }
        )
    );
//    setThread(
//        boost::shared_ptr<BabelUtils::BoostThread>(new BabelUtils::BoostThread(
//            [this] { this->launch_listener(); }
//            )
//        )
//    );
}

void AsioListener::launch_listener()
{
    while (isReady()) {
        try {
            accept();
            startContext();
        } catch (const BabelErrors::ClientError &e) {
            std::cerr << "ERROR IN HANDLE READ DATA INFOS (Client Stopped) " << e.what() << std::endl;
            e.getClient().stop();
        }
    }
}

void AsioListener::accept()
{
    std::cout << "ACCEPT" << std::endl;

    _asioClients.emplace_back(
        boost::make_shared<BabelNetwork::AsioClientSocket>(
            _networkInfos.getIp(),
            _networkInfos.getPortStr(),
            _logger,
            _context,
            BabelNetwork::AsioClientSocket::SocketHandler::Server
        )
    );
    auto new_session = _asioClients.back();

    _acceptor.async_accept(
        new_session->getSocket(),
        boost::bind(&AsioListener::handle_accept, this, new_session, boost::asio::placeholders::error)
    );
}

void AsioListener::stop()
{
    std::cout << "LISTENER STOPPED" << std::endl;
    stopContext();
    _acceptor.close();
    _signals.clear();
}

void AsioListener::handle_accept(
    const boost::shared_ptr<BabelNetwork::AsioClientSocket> &session,
    const boost::system::error_code &error
)
{
    if (!error) {
        auto s = BabelUtils::format("Incoming connexion from %s with port %u",
            session->getSocket().remote_endpoint().address().to_string().c_str(),
            session->getSocket().remote_endpoint().port()
        );
        _logger.logThis(s);
        dbg("%s", s.c_str())
        std::cout << s << std::endl;
        try {
            session->start();
        } catch (const std::runtime_error &e) {
            std::cout << "In Session Execution\n" << e.what() << std::endl;
        }
    }
    accept();
}

void AsioListener::setSignalsHandeled()
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
//    _signals.async_wait(boost::bind(&AsioListener::stop, this));
    _signals.async_wait(boost::bind(&AsioListener::stopContext, this));
}

void AsioListener::startContext()
{
    std::cout << "CONTEXT LAUNCHED on " << _networkInfos << std::endl;
    _context.run();
    std::cout << "CONTEXT FINISHED on " << _networkInfos << std::endl;
}

void AsioListener::stopContext()
{
    if (!_context.stopped())
        _context.stop();
    setNotReady();
}

[[nodiscard]] const signal_set &AsioListener::getSignals() const
{
    return _signals;
}

[[nodiscard]] const ip::tcp::endpoint &AsioListener::getEndpoint() const
{
    return _endpoint;
}

[[nodiscard]] const ip::tcp::acceptor &AsioListener::getAcceptor() const
{
    return _acceptor;
}

[[nodiscard]] io_context &AsioListener::getContext() const
{
    return const_cast<io_context &>(_context);
}
