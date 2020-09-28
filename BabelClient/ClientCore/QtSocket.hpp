#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "AResponse.hpp"
#include "ITcpSocket.hpp"

class MyTcpSocket : public QObject, virtual public ITcpSocket {
Q_OBJECT
public:
    MyTcpSocket(QObject *parent = nullptr);

    ~MyTcpSocket();

    void doConnect(const std::string &ip, int port);

    void disconnect();

    void sendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);

    std::shared_ptr<BabelNetwork::AResponse> readResponse();

signals:

public slots:

    void connected();

    void disconnected();

    void bytesWritten(const qint64 bytes);

private:
    QTcpSocket *socket;
};
