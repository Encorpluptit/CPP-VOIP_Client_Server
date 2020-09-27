
#include "AResponse.hpp"

class ISocket
{
    public:
        virtual void doConnect(const std::string &ip, int port) = 0;
        virtual void writeData(const std::shared_ptr<BabelNetwork::AResponse> &response) = 0;
        virtual std::shared_ptr<BabelNetwork::AResponse> readResponse() = 0;

    private:

};