/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/27/20).
** File description:
** [AsioListener.cpp]: Source file for AsioListener feature.
*/

#include <iostream>
#include "AsioListener.hpp"

using namespace BabelServer;

AsioListener::AsioListener(const std::string &address, const std::string &port, BabelUtils::Logger &logger)
    : BabelNetwork::ASocket(address, port, logger),
      _endpoint(ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()),
      _acceptor(_context, _endpoint),
      _signals(_context)
{
    setReady();
    setSignalsHandeled();
    setThread(
        boost::make_shared<BabelUtils::BoostThread>(
        [this] {this->start();}
        )
    );
}

AsioListener::~AsioListener()
{
    _asioClients.clear();
    _read_msg.reset();
    while (!_read_queue.empty())
        _read_queue.pop();
    while (!_write_queue.empty())
        _write_queue.pop();
}

void AsioListener::start()
{
    std::cout << "START / RESTART" << std::endl;

    accept();
    startContext();
}


void AsioListener::accept()
{
    std::cout << "ACCEPT" << std::endl;

    _asioClients.emplace_back(
        boost::make_shared<BabelNetwork::AsioClientSocket>(
        _networkInfos.getIp(),
            _networkInfos.getPortStr(),
            _context,
            BabelNetwork::AsioClientSocket::SocketHandler::Server,
            _logger
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
    if (!_context.stopped())
        _context.stop();
    getThread()->stop();
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
    _signals.async_wait(boost::bind(&AsioListener::stop, this));
}

void AsioListener::startContext() {
    std::cout << "CONTEXT LAUNCHED on " << _networkInfos << std::endl;
    _context.run();
    std::cout << "CONTEXT FINISHED on " << _networkInfos << std::endl;
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

[[nodiscard]] io_context &AsioListener::getContext() const {
    return const_cast<io_context &>(_context);
}

