#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include "AResponse.hpp"
#include "IUdpSocket.hpp"

class MyUdpSocket : public QObject, virtual public IUdpSocket {
Q_OBJECT
public:
    explicit MyUdpSocket(QObject *parent = nullptr);

    ~MyUdpSocket() override;

    void doConnect(int port) override;

    void disconnect() override;

    void sendVoice(const std::vector<uint16_t> &voice, const std::string &ip, int port) override;

    std::vector<uint16_t> readVoice(const std::string &ip, int port) override;

    /*void readData(std::string ip, int port);

    void sendData(std::string data, std::string ip, int port);*/

signals:

public slots:

    void connected();

    void disconnected();

    void bytesWritten(qint64 bytes);

private:
    QUdpSocket *socket;
};
