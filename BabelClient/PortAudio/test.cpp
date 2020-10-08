/*
** EPITECH PROJECT, 2020
** Test.cpp
** File description:
** Test.cpp
*/

#include <arpa/inet.h>
#include <iostream>
#include "Core.hpp"
#include "Exception.hpp"

#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (480)

bool error()
{
    Pa_Terminate();
    return (false);
}

Core::Core(const std::string ip, const std::string port)
{
    int err;

    socket = new QUdpSocket();
    socket->bind(QHostAddress("81.250.229.32"), std::stoi("8000"));
    if (Pa_Initialize() != paNoError)
        throw (Exception("Pa_Initialize failed"));
    encoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &err);
    if (err != OPUS_OK)
        throw (Exception("Encoder create failed"));
    decoder = opus_decoder_create(48000, 1, &err);
    if (err != OPUS_OK)
        throw (Exception("Decoder create failed"));
    Loop(ip, port);
}

bool Core::init_audio()
{
    if (Pa_OpenDefaultStream(&stream, 1, 1, paInt16, 48000, 480, nullptr, nullptr) != paNoError)
        return (error());
    if (Pa_StartStream(stream) != paNoError)
        return (error());
    return (true);
}

bool Core::stop_audio()
{
    if (Pa_CloseStream(stream) != paNoError)
        return (error());
    return (true);
}

void Core::Loop(const std::string ip, const std::string port) noexcept
{
    std::vector<uint16_t> voice;

    //init_input();
    //init_output();
    init_audio();
    std::cout << "Press a key when the two client are running" << std::endl;
    getchar();
    //printf("Connect = %d\n", connect(ip, port));
    while (1) {
        voice = getVoice();
        voice = encode(voice);
        voice = decode(voice);
        playVoice(voice);
    }
    stop_audio();
}

std::vector<uint16_t> Core::encode(std::vector<uint16_t> voice)
{
    std::vector<uint16_t> compressed(voice.size());
    int bytes = opus_encode(encoder, (opus_int16 const *) voice.data(), (int) voice.size(),
        (unsigned char *) compressed.data(), (int) compressed.size());
    if (bytes < 0)
        throw (Exception("Compression error"));
    return (compressed);
}

std::vector<uint16_t> Core::decode(std::vector<uint16_t> voice)
{
    std::vector<uint16_t> decompressed(voice.size());
    int bytes = opus_decode(decoder, (unsigned char *) voice.data(), (int) voice.size(),
        (opus_int16 *) decompressed.data(), (int) decompressed.size(), 0);
    if (bytes < 0)
        throw (Exception("Compression error"));
    return (decompressed);
}

std::vector<uint16_t> Core::getVoice()
{
    long len = Pa_GetStreamReadAvailable(stream);
    std::vector<uint16_t> record(480);

    if (len < 0)
        throw (Exception("getVoice"));
    if (len < (long) 480)
        Pa_ReadStream(stream, record.data(), (unsigned long) len);
    else
        Pa_ReadStream(stream, record.data(), 480);
    return (record);
}

void Core::playVoice(std::vector<uint16_t> record)
{
    long len = 0;
    while ((len = Pa_GetStreamWriteAvailable(stream)) < (long) record.size());
    Pa_WriteStream(stream, record.data(), (unsigned long) record.size());
}

bool Core::connect(std::string ip, std::string port) noexcept
{
    socket->connectToHost(QHostAddress(ip.c_str()), std::stoi(port));
    if (socket->waitForConnected(1000) != false)
        return (true);
    return (false);
}

bool Core::writeData(const std::string str) noexcept
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(str.c_str(), str.size());
        return (socket->waitForBytesWritten());
    }
    return (false);
}

Core::~Core() noexcept
{
    if (encoder)
        opus_encoder_destroy(encoder);
    if (decoder)
        opus_decoder_destroy(decoder);
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    delete socket;
}

int main(int ac, char **av)
{
    try {
        (void) av;
        if (ac != 3)
            return (84);
        Core prog(av[1], av[2]);
        return (0);
    } catch (Exception &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
}











/*bool Core::init_input()
{
    input.device = Pa_GetDefaultInputDevice();
    if (input.device == paNoDevice)
        return (error());
    input.channelCount = 2;
    input.sampleFormat = paFloat32;
    input.suggestedLatency = Pa_GetDeviceInfo(input.device)->defaultLowInputLatency;
    input.hostApiSpecificStreamInfo = NULL;
    return (true);
}*/

/*bool Core::init_output()
{
    output.device = Pa_GetDefaultOutputDevice();
    if (output.device == paNoDevice)
        return (error());
    output.channelCount = 2;
    output.sampleFormat = paFloat32;
    output.suggestedLatency = Pa_GetDeviceInfo(output.device)->defaultLowOutputLatency;
    output.hostApiSpecificStreamInfo = NULL;
    return (true);
}*/