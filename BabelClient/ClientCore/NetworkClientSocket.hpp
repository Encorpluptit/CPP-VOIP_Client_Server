
#include "AResponse.hpp"
#include "QtSocket.hpp"
#include "IUdpSocket.hpp"

class NetworkClientSocket {
public:
    NetworkClientSocket(const std::string &ip, const int port) : serverIp(ip), serverPort(port) {}

    ~NetworkClientSocket()
    {
        //destroyTcpSocket();
        //destroyUdpSocket();
    }

    void createUdpSocket() {}

    void createTcpSocket()
    {
        _tcp = std::make_shared<MyTcpSocket>();
    }

    void destroyTcpSocket()
    {
        _tcp->disconnect();
    }

    void destroyUdpSocket() {}

    void run()
    {
        createTcpSocket();
        _tcp->doConnect(serverIp, serverPort);
    }

    std::shared_ptr<ITcpSocket> getTcp()
    {
        return (_tcp);
    }

    std::shared_ptr<IUdpSocket> getUdp()
    {
        return (_udp);
    }

private:
    std::shared_ptr<ITcpSocket> _tcp;
    std::shared_ptr<IUdpSocket> _udp;
    std::string serverIp;
    int serverPort;
};