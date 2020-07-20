/*
** EPITECH PROJECT, 2020
** Core
** File description:
** Core
*/

#include <QtNetwork/QUdpSocket>

class Core
{
    public:
        Core();
        ~Core() noexcept;
    private:
        QUdpSocket *socket;
};