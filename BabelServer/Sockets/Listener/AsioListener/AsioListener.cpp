/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioListener.cpp]: Source file for AsioListener feature.
*/

#include <iostream>
#include "AsioListener.hpp"
#include "BoostThread.hpp"
#include "Debug.hpp"
#include "ClientError.hpp"

using namespace BabelServer;

AsioListener::AsioListener(
    const std::string &address,
    const std::string &port,
    BabelUtils::Logger &logger
)
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
}

void AsioListener::start()
{
    std::cout << "START / RESTART" << std::endl;

    auto s = BabelUtils::format("Local connexion from %s with port %u",
        _acceptor.local_endpoint().address().to_string().c_str(),
        _acceptor.local_endpoint().port()
    );
    _logger.logThis(s);
    setThread(
        boost::make_shared<BabelUtils::BoostThread>(
            [this] { this->launch_listener(); }
        )
    );
    setReady();
}

void AsioListener::launch_listener()
{
    bool context_launched = false;

    while (isReady()) {
        try {
            accept();
            if (!context_launched) {
                context_launched = true;
                startContext();
            }
        } catch (const BabelErrors::ClientError &e) {
            std::cerr << "ERROR IN HANDLE READ DATA INFOS (Client Stopped) " << e.what() << std::endl;
            e.getClient().stop();
        }
    }
}

void AsioListener::accept()
{
    std::string log("Listener Starting to Accept !");
    _logger.logThis(log);
    dbg("%s", log.c_str());
    auto port = std::to_string(_networkInfos.getPort());

    auto new_session = BabelUtils::makeSharedPtr<AsioClientSocket>(
        _networkInfos.getIp(),
        port,
        _logger,
        _context,
        _clientsList
    );

    _acceptor.async_accept(
        new_session->getSocket(),
        boost::bind(&AsioListener::handle_accept, this, new_session, boost::asio::placeholders::error)
    );
}

void AsioListener::stop()
{
    std::cout << "LISTENER STOPPED" << std::endl;
    setNotReady();
    _signals.clear();
    if (_acceptor.is_open())
        _acceptor.close();
    stopContext();
}

void AsioListener::handle_accept(
    const BabelUtils::SharedPtr<AsioClientSocket> &session,
    const boost::system::error_code &error
)
{
    if (!error) {
        auto s = BabelUtils::format("Incoming connexion from %s with port %u",
            session->getSocket().remote_endpoint().address().to_string().c_str(),
            session->getSocket().remote_endpoint().port()
        );
        _logger.logThis(s);
        dbg("%s", s.c_str());
        session->setIp(session->getSocket().remote_endpoint().address().to_string());
        session->setPort(session->getSocket().remote_endpoint().port());
        try {
            session->start();
        } catch (const BabelErrors::ClientError &e) {
            auto log = BabelUtils::format("In Session Execution : %s\n", e.what());
            _logger.logThis(log);
            dbg("%s", log.c_str())
        }
    } else {
        std::cerr << error << std::endl;
    }
    _clientsList.add_client(session);
    accept();
}

void AsioListener::setSignalsHandeled()
{
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
    _signals.async_wait(boost::bind(&AsioListener::stop, this));
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

[[nodiscard]] const BabelUtils::SharedPtr<BabelUtils::AThread> &AsioListener::getThread() const
{
    return _thread;
}

void AsioListener::setThread(const BabelUtils::SharedPtr<BabelUtils::AThread> &thread)
{
    _thread = thread;
}

