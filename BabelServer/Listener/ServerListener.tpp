/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/16/20).
** File description:
** [Listener.hpp]: Header file for ServerListenerpp feature.
*/

#ifndef CPP_BABEL_2020_SERVERLISTENER_HPP
#define CPP_BABEL_2020_SERVERLISTENER_HPP

#include <memory>
#include <utility>
#include "AsioSocket.tpp"

class ClientSocket : public boost::enable_shared_from_this<ClientSocket> {
public:
    ClientSocket(boost::asio::io_context &io_context, const std::string &msg)
        : _socket(io_context), _msg(msg)
    {
    }

    boost::asio::ip::tcp::socket &socket()
    {
        return _socket;
    }

    void start_session()
    {
        std::cout << "START SESSION" << std::endl;
        boost::asio::async_read(
            _socket,
            boost::asio::buffer(_data, DATALENGTH),
            boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
        );
    }

    void deliver(const std::string &msg)
    {
        std::cout << "START DELIVER" << std::endl;
        boost::asio::async_write(
            _socket,
            boost::asio::buffer(_msg.c_str(), _msg.length()),
            boost::bind(&ClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
        );
//        bool write_in_progress = !write_msgs_.empty();
//        std::cout << "START DELIVER" << std::endl;
//        write_msgs_.push_back(msg);
//        if (!write_in_progress) {
//            boost::asio::async_write(
//                socket_,
//                boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
//                boost::bind(&ClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
//            );
//        }
    }

    void handle_read_header(const boost::system::error_code &error)
    {
        if (!error) {
            std::cout << "START READ HEADER" << std::endl;
            std::cout << "Data before :" << _data << std::endl;
            boost::asio::async_read(_socket,
                boost::asio::buffer(_data, DATALENGTH),
                boost::bind(&ClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
            );
            std::cout << "Data After :" << _data << std::endl;
        } else {
            std::cerr << "ERROR IN HANDLE READ HEADER (close here ?)" << std::endl;
//            room_.leave(shared_from_this());
        }
//        if (!error && read_msg_.decode_header()) {
//            std::cout << "START READ HEADER" << std::endl;
//            boost::asio::async_read(socket_,
//                boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//                boost::bind(&ClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
//            );
//        } else {
//            room_.leave(shared_from_this());
//        }
    }

    void handle_read_body(const boost::system::error_code &error)
    {
        if (!error) {
            std::cout << "START READ BODY" << std::endl;
            std::cout << "Data before :" << _data << std::endl;
            boost::asio::async_read(_socket,
                boost::asio::buffer(_data, DATALENGTH),
                boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
            );
            std::cout << "Data After :" << _data << std::endl;
        } else {
            std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
        }
//        if (!error) {
//            std::cout << "START READ BODY" << std::endl;
//            boost::asio::async_read(
//                socket_,
//                boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//                boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
//            );
//        } else {
//            std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
//            room_.leave(shared_from_this());
//        }
    }

    void handle_write(const boost::system::error_code &error)
    {
        if (!error) {
            boost::asio::async_write(
                _socket,
                boost::asio::buffer(_msg.c_str(), _msg.length()),
                boost::bind(&ClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
        } else {
            std::cerr << "ERROR IN HANDLE WRITE" << std::endl;
            //room_.leave(shared_from_this());
        }
    }

private:
    boost::asio::ip::tcp::socket _socket;
    std::string _msg;
    static const size_t DATALENGTH = 3;
    char _data[DATALENGTH] = {0};
};

// TODO: change namespace
// TODO: template in common and ListenerClass derived from AsioSocket<Listener> ?
namespace BabelNetwork {
    template<>
    class AsioSocket<Listener> final : virtual public ASocket {
    public:
        explicit AsioSocket(const NetworkInfos &nwInfos)
            : ASocket(nwInfos),
              _context(new boost::asio::io_context),
              _acceptor(boost::asio::ip::tcp::acceptor(
                  *_context,
                  boost::asio::ip::tcp::endpoint(
                      boost::asio::ip::address::from_string(_networkInfos.getIp()), _networkInfos.getPort()
                  ))
              ),
              _signals(*_context)
        {
            setReady();
            setSignalsHandeled();
            start();
            setThread(boost::make_shared<BabelUtils::BoostThread>(
                [this] {
                    std::cout << "THREAD LAUNCHED" << std::endl;
                    _context->run();
                    std::cout << "THREAD FINISHED" << std::endl;
                }
                )
            );
        }

        ~AsioSocket() final
        {
            stop();
        }

        /* <- Methods -> */
    public:
        void start() final
        {
            boost::shared_ptr<ClientSocket> new_session(new ClientSocket(*_context, "msg"));
            _acceptor.async_accept(
                new_session->socket(),
                boost::bind(&AsioSocket<Listener>::handle_accept, this, new_session, boost::asio::placeholders::error)
            );
        };

        void stop() final
        {
            std::cout << "LISTENER STOPPED" << std::endl;
            _context->stop();
        };

        [[nodiscard]] bool sendResponse(const AResponse &response) final
        {
            std::cerr << "Listener cannot send responses" << std::endl;
            return false;
        };


        void handle_accept(const boost::shared_ptr<ClientSocket> &session, const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "ACCEPT OK" << std::endl;
                session->start_session();
            }
            start();
        }

        void setSignalsHandeled()
        {
            _signals.add(SIGINT);
            _signals.add(SIGTERM);
            _signals.async_wait(boost::bind(&AsioSocket::stop, this));
        }

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const boost::shared_ptr<boost::asio::io_context> &getContext() const
        {
            return _context;
        }


        /* <- Attributes -> */
    private:
        boost::shared_ptr<boost::asio::io_context> _context;
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::signal_set _signals;
    };

}

#endif /* CPP_BABEL_2020_SERVERLISTENER_HPP */
