
#include <memory>
#include <iostream>
#include "QUdpSocket.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

MyUdpSocket::MyUdpSocket(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
}

MyUdpSocket::~MyUdpSocket()
{
    delete socket;
}

void MyUdpSocket::doConnect(const std::string &ip, int port)
{
    socket->bind(QHostAddress(ip.c_str()), port);
}

void MyUdpSocket::disconnect()
{
    socket->disconnect();
}

void MyUdpSocket::connected()
{
    qDebug() << "connected...";
}

void MyUdpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void MyUdpSocket::bytesWritten(const qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

std::vector<uint16_t> MyUdpSocket::readResponse(std::string ip, int port)
{
    std::vector<uint16_t> voice;
    QHostAddress addr;
    quint16 portIncoming;
    int bytes;
    char *date_transform;

    if ((bytes = socket->bytesAvailable()) < 1)
        return (voice);
    char data[bytes];
    socket->readDatagram(data, bytes, &addr, &portIncoming);
    if (addr.toString() != ip.c_str() || portIncoming != port)
        return (voice);
    std::vector<uint16_t> voice2(date_transform, sizeof(data));
    return (voice);
}

void MyUdpSocket::sendResponse(std::vector<uint16_t> buf, std::string ip, int port)
{
    QString str = ip.c_str();
    QHostAddress addr;

    addr.setAddress(str);

    QByteArray data = reinterpret_cast<const char*>(buf.data(), buf.size());
    socket->writeDatagram(data, addr, port);
}