#include "QtSocket.hpp"

QtSocket::QtSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
}

void QtSocket::Binding(int port)
{
    socket->bind(QHostAddress::LocalHost, port);
}

bool QtSocket::sendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    (void)response;
    return (true);
}