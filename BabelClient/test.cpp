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

Core::Core(const std::string ip, const std::string port) noexcept
{
    socket = new QTcpSocket();
    if (Pa_Initialize() != paNoError)
        throw(Exception("Pa_Initialize failed"));
    Loop(ip, port);
}

bool Core::init_input()
{
    input.device = Pa_GetDefaultInputDevice();
    if (input.device == paNoDevice)
        return (error());
    input.channelCount = 2;
    input.sampleFormat = paFloat32;
    input.suggestedLatency = Pa_GetDeviceInfo(input.device)->defaultLowInputLatency;
    input.hostApiSpecificStreamInfo = NULL;
    return (true);
}

bool Core::init_output()
{
    output.device = Pa_GetDefaultOutputDevice();
    if (output.device == paNoDevice)
        return (error());
    output.channelCount = 2;
    output.sampleFormat = paFloat32;
    output.suggestedLatency = Pa_GetDeviceInfo(output.device)->defaultLowOutputLatency;
    output.hostApiSpecificStreamInfo = NULL;
    return (true);
}

bool Core::init_audio()
{
    if (Pa_OpenStream(&stream, &input, &output, SAMPLE_RATE, FRAMES_PER_BUFFER, 0, NULL, NULL) != paNoError)
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
    init_input();
    init_output();
    init_audio();
    std::cout << "Press a key when the two client are running" << std::endl;
    getchar();
    /*connect(ip, std::stoi(ip));
    while (1) {
        //receive_voice;
        //send_voice;
    }*/
    stop_audio();
}

bool Core::connect(const std::string ip, const int port) noexcept
{
    socket->connectToHost(QString::fromStdString(ip), port);
    if (socket->waitForConnected(1000) == false)
        return (false);
    return (true);
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
    socket->disconnectFromHost();
    socket->waitForDisconnected();
    delete socket;
}

int main(int ac, char **av)
{
    try {
    if (ac != 2)
        return (84);
    Core prog();
    return (0);
    } catch (Exception& err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
}