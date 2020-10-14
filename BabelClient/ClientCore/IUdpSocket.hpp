#pragma once

#include "AResponse.hpp"

class IUdpSocket {
public:
    virtual void doConnect(int port) = 0;

    virtual void disconnect() = 0;

    virtual void sendVoice(const std::vector<uint16_t> &voice, const std::string &ip, int port) = 0;

    virtual std::vector<uint16_t> readVoice(const std::string &ip, int port) = 0;

    /*virtual void readData(std::string ip, int port) = 0;

    virtual void sendData(std::string data, std::string ip, int port) = 0;*/

private:
};