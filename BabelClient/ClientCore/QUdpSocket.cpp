
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

std::vector<uint16_t> MyUdpSocket::readVoice(std::string ip, int port)
{
    std::vector<uint16_t> voice;
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;

    if (socket->hasPendingDatagrams() == false)
        return (voice);
    data.resize(socket->pendingDatagramSize());
    socket->readDatagram(data.data(), data.size(), &sender, &senderPort);
    if (sender.toString().toLocal8Bit().constData() != ip || senderPort != port)
        return (voice);
    std::vector<uint16_t> voice2(data.begin(), data.end());
    return (voice2);
}

void MyUdpSocket::sendVoice(std::vector<uint16_t> buf, std::string ip, int port)
{
    QString str = ip.c_str();
    QHostAddress addr;

    addr.setAddress(str);

    QByteArray data = reinterpret_cast<const char *>(buf.data(), buf.size() * 2);
    socket->writeDatagram(data, addr, port);
}