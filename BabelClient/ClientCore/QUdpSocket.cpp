
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

std::vector<uint16_t> MyUdpSocket::readVoice(const std::string &ip, int port)
{
    std::vector<uint16_t> voice{};
    QByteArray buf{};
    QHostAddress sender{};
    quint16 senderPort{};

    if (!socket->hasPendingDatagrams())
        return (voice);
    buf.resize(socket->pendingDatagramSize());
    socket->readDatagram(buf.data(), socket->pendingDatagramSize(), &sender, &senderPort);
    if (sender.toString().toLocal8Bit().constData() != ip || senderPort != port)
        return (voice);
    void *data = buf.data();
    uint16_t *tmp = (uint16_t *)data;
    std::vector<uint16_t> voice2(tmp, tmp + buf.length());
    voice2.resize(480);
    return (voice2);
}

void MyUdpSocket::sendVoice(const std::vector<uint16_t> &buf, const std::string &ip, int port)
{
    QString str = ip.c_str();
    QHostAddress addr;

    addr.setAddress(str);

    QByteArray data = reinterpret_cast<const char *>(buf.data());
    socket->writeDatagram(data, addr, port);
}

/*void MyUdpSocket::readData(std::string ip, int port)
{
    std::string str = "";
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;

    if (socket->hasPendingDatagrams() == false)
        return;
    data.resize(socket->pendingDatagramSize());
    socket->readDatagram(data.data(), data.size(), &sender, &senderPort);
    qDebug() << "MESSAGE : " << data << " SENDER IP :" << sender << " SENDER PORT : " << senderPort;
}

void MyUdpSocket::sendData(std::string data, std::string ip, int port)
{
    QHostAddress addr;

    addr.setAddress(ip.c_str());
    socket->writeDatagram(data.c_str(), addr, port);
}*/