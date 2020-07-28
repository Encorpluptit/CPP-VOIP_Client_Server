/*
** EPITECH PROJECT, 2020
** Core
** File description:
** Core
*/

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <opus/opus.h>
#include <portaudio.h>

class Core
{
    public:
        Core(const std::string ip, const std::string port);
        void Loop(const std::string ip, const std::string port) noexcept;
        bool connect(std::string ip, std::string port) noexcept;
        bool writeData(std::string str) noexcept;
        bool init_audio();
        //bool init_input();
        //bool init_output();
        bool stop_audio();
        std::vector<uint16_t> getVoice();
        void playVoice(std::vector<uint16_t> record);
        std::vector<uint16_t> encode(std::vector<uint16_t> voice);
        std::vector<uint16_t> decode(std::vector<uint16_t> voice);
        ~Core() noexcept;
    private:
        QUdpSocket *socket;
        PaStreamParameters input;
        PaStreamParameters output;
        PaStream *stream;
        OpusEncoder *encoder;
        OpusDecoder *decoder;
};