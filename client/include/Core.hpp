/*
** EPITECH PROJECT, 2020
** Core
** File description:
** Core
*/

#include <QtNetwork/QUdpSocket>

class Core : public QObject
{
    public:
        Core();
        void HelloUDP();
        ~Core() noexcept;

    public slots:
        void readyRead();
    private:
        QUdpSocket *socket;
};