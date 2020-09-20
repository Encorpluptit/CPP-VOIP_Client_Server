#pragma once

#include <QObject>
#include <QTcpSocket>
#include "AResponse.hpp"

class QtSocket : public QObject
{
    Q_OBJECT

    public:
        explicit QtSocket(QObject *parent = 0);
        void Binding(int port);
        bool sendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        QTcpSocket *socket;

    public slots:
    private:

};