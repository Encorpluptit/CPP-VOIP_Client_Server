#pragma once

#include "AResponse.hpp"

class IUdpSocket {
public:
    virtual void doConnect(const std::string &ip, int port) = 0;

    virtual void disconnect() = 0;

    virtual void sendVoice(std::vector<uint16_t> voice, std::string ip, int port) = 0;

    virtual std::vector<uint16_t> readVoice(std::string ip, int port) = 0;

    virtual void readData(std::string ip, int port) = 0;

    virtual void sendData(std::string data, std::string ip, int port) = 0;

    virtual std::vector<uint16_t> readVoix(std::string ip, int port) = 0;

private:
};