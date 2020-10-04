#pragma once

#include "AResponse.hpp"

class IUdpSocket {
public:
    virtual void doConnect(const std::string &ip, int port) = 0;

    virtual void disconnect() = 0;

    virtual void sendResponse(std::vector<uint16_t> voice, std::string ip, int port) = 0;

    virtual std::vector<uint16_t> readResponse(std::string ip, int port) = 0;

private:
};