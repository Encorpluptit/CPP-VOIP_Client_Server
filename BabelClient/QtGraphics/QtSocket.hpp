#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "AResponse.hpp"

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    
    void doConnect(const std::string &ip, int port);
    void writeData(const std::shared_ptr<BabelNetwork::AResponse> &response);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(const qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
    
};
