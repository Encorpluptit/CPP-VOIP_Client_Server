/*
** EPITECH PROJECT, 2020
** Core
** File description:
** Core
*/

#include <QtNetwork/QTcpSocket>
#include "portaudio.h"

class Core
{
    public:
        Core(const std::string ip, const std::string port) noexcept;
        void Loop(const std::string ip, const std::string port);
        bool connect(const std::string ip, const int port);
        bool writeData(std::string str);
        bool init_audio();
        bool init_input();
        bool init_output();
        bool stop_audio();
        ~Core();
    private:
        QTcpSocket *socket;
        PaStreamParameters input;
        PaStreamParameters output;
        PaStream *stream;
};