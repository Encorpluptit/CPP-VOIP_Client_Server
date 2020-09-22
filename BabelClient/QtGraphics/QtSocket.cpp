
#include <memory>
#include <iostream>
#include "QtSocket.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

MyTcpSocket::MyTcpSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

void MyTcpSocket::doConnect(const std::string &ip, int port)
{
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    //connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting...";
    socket->connectToHost(ip.c_str(), port);
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void MyTcpSocket::connected()
{
    qDebug() << "connected...";
}

void MyTcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(const qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

std::shared_ptr<BabelNetwork::AResponse> MyTcpSocket::readResponse()
{
    char header[BabelNetwork::AResponse::HeaderSize];

    socket->read(header, BabelNetwork::AResponse::HeaderSize);
    auto resp = BabelNetwork::AResponse::getResponse(header);
    socket->read(resp->getDataByteDataInfos(), resp->getDataInfosSize());
    resp->decode_data_infos();
    socket->read(resp->getDataByteBody(), resp->getDataSize());
    resp->decode_data();
    return (resp);
}

void MyTcpSocket::writeData(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    response->encode();
    socket->write(response->getDataByte(), response->getResponseSize());
}