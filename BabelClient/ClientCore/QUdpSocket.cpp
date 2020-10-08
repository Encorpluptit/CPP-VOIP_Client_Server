
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
    std::vector<uint16_t> voice{};
    QByteArray data{};
    QHostAddress sender{};
    quint16 senderPort{};

    if (socket->hasPendingDatagrams() == false) {
        //std::cout << "DATAGRAM FALSE" << std::endl;
        return (voice);
    }
    data.resize(socket->pendingDatagramSize());
    //std::cout << "SIZE DATAGRAM : " << socket->pendingDatagramSize() << std::endl;
    socket->readDatagram(data.data(), socket->pendingDatagramSize(), &sender, &senderPort);
    if (sender.toString().toLocal8Bit().constData() != ip || senderPort != port) {
        std::cout << "IP / PORT FALSE" << std::endl;
        return (voice);
    }
    std::vector<uint16_t> voice2(data.begin(), data.end());
    voice2.resize(480);
    //std::cout << "SIZE PACKET RECEIVE : " << voice2.size() << std::endl;
    return (voice2);
}

void MyUdpSocket::sendVoice(std::vector<uint16_t> buf, std::string ip, int port)
{
    QString str = ip.c_str();
    QHostAddress addr;

    addr.setAddress(str);

    //std::cout << "SIZE PACKET SEND : " << buf.size() << std::endl;
    QByteArray data = reinterpret_cast<const char *>(buf.data());
    socket->writeDatagram(data, addr, port);
}

void MyUdpSocket::readData(std::string ip, int port)
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

std::vector<uint16_t> MyUdpSocket::readVoix(std::string ip, int port)
{
    std::string str = "";
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;
    std::vector<uint16_t> empty;

    if (socket->hasPendingDatagrams() == false)
        return (empty);
    data.resize(socket->pendingDatagramSize());
    socket->readDatagram(data.data(), data.size(), &sender, &senderPort);
    std::vector<uint16_t> voice(data.begin(), data.end());
    qDebug() << "MESSAGE : " << data << " SENDER IP :" << sender << " SENDER PORT : " << senderPort;
    return (voice);
}

void MyUdpSocket::sendData(std::string data, std::string ip, int port)
{
    QHostAddress addr;

    addr.setAddress(ip.c_str());
    socket->writeDatagram(data.c_str(), addr, port);
}