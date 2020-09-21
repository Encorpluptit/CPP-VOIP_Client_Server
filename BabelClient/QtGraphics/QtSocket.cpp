
#include <memory>
#include <iostream>
#include "QtSocket.hpp"

MyTcpSocket::MyTcpSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

void MyTcpSocket::doConnect(const std::string &ip, int port)
{
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
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

void MyTcpSocket::readyRead()
{
    qDebug() << "reading...";

    qDebug() << socket->readAll();
}

void MyTcpSocket::writeData(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    socket->write(response->getDataByte(), response->getResponseSize());
}