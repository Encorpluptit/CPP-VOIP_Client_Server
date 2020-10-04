
#include "AResponse.hpp"
#include "QtSocket.hpp"
#include "QUdpSocket.hpp"

class NetworkClientSocket {
public:
    NetworkClientSocket(const std::string &ip, const int port) : serverIp(ip), serverPort(port)
    {
        _tcp = nullptr;
        _udp = nullptr;
    }

    ~NetworkClientSocket()
    {
        //destroyTcpSocket();
        //destroyUdpSocket();
    }

    void createUdpSocket()
    {
        _udp = std::make_shared<MyUdpSocket>();
    }

    void destroyUdpSocket()
    {
        _udp->disconnect();
    }

    void createTcpSocket()
    {
        _tcp = std::make_shared<MyTcpSocket>();
    }

    void destroyTcpSocket()
    {
        _tcp->disconnect();
    }

    void run()
    {
        createUdpSocket();
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

    void setIpPort(int port)
    {
        myUdpIp = "127.0.0.1";
        myUdpPort = port;
    }

    std::string myUdpIp;
    int myUdpPort;
    
private:
    std::shared_ptr<ITcpSocket> _tcp;
    std::shared_ptr<IUdpSocket> _udp;
    std::string serverIp;
    int serverPort;
};