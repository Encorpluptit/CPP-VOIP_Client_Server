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
    explicit MyTcpSocket(QObject *parent = nullptr);

    ~MyTcpSocket() override;

    void doConnect(const std::string &ip, int port) override;

    void disconnect() override;

    void sendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response) override;

    std::shared_ptr<BabelNetwork::AResponse> readResponse() override;

signals:

public slots:

    void connected();

    void disconnected();

    void bytesWritten(qint64 bytes);

private:
    QTcpSocket *socket;
};
