#pragma once

#include "AResponse.hpp"

class IUdpSocket {
public:
    virtual void doConnect(const std::string &ip, int port) = 0;

    virtual void disconnect() = 0;

    virtual void sendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response) = 0;

    virtual std::shared_ptr<BabelNetwork::AResponse> readResponse() = 0;

private:
};