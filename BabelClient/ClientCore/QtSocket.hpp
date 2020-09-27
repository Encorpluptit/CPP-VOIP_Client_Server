#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "AResponse.hpp"
#include "ISocket.hpp"

class MyTcpSocket : public QObject, public ISocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    
    void doConnect(const std::string &ip, int port);
    void writeData(const std::shared_ptr<BabelNetwork::AResponse> &response);

    QTcpSocket *socket;

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(const qint64 bytes);
    std::shared_ptr<BabelNetwork::AResponse> readResponse();
    
};
