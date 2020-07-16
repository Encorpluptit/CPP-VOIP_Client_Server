/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/16/20).
** File description:
** [Client.hpp]: Header file for Clientpp feature.
*/

#ifndef CPP_BABEL_2020_CLIENT_HPP
#define CPP_BABEL_2020_CLIENT_HPP

#include "AsioSocket.tpp"

namespace BabelServer {
    class ClientSocket final
        : public boost::enable_shared_from_this<ClientSocket>,
          virtual public BabelNetwork::AsioSocket<boost::asio::ip::tcp::socket> {
    public:
        ClientSocket(boost::asio::io_context &io_context, const BabelNetwork::NetworkInfos &nwInfos,
            const std::string &msg)
            : ASocket(nwInfos), BabelNetwork::AsioSocket<boost::asio::ip::tcp::socket>(io_context, nwInfos), _msg(msg)
        {
        }

        ~ClientSocket() final
        {
            do_close();
        }

        void start() final
        {
            std::cout << "START SESSION" << std::endl;
            boost::asio::async_read(
                getSocket(),
                boost::asio::buffer(_data, DATALENGTH),
                boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
            );
        }

        bool sendResponse(const BabelNetwork::AResponse &response) final
        {
            std::cout << "START DELIVER" << std::endl;
            boost::asio::async_write(
                getSocket(),
                boost::asio::buffer(_msg.c_str(), _msg.length()),
                boost::bind(&ClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
            );
            return true;
        }

        void handle_read_header(const boost::system::error_code &error)
        {
            if (!error) {
                std::cout << "START READ HEADER" << std::endl;
                std::cout << "Data before :" << _data << std::endl;
                boost::asio::async_read(getSocket(),
                    boost::asio::buffer(_data, DATALENGTH),
                    boost::bind(&ClientSocket::handle_read_body, shared_from_this(), boost::asio::placeholders::error)
                );
                std::cout << "Data After :" << _data << std::endl;
            } else {
                std::cerr << "ERROR IN HANDLE READ HEADER (close here ?)" << std::endl;
                stop();
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
                boost::asio::async_read(getSocket(),
                    boost::asio::buffer(_data, DATALENGTH),
                    boost::bind(&ClientSocket::handle_read_header, shared_from_this(), boost::asio::placeholders::error)
                );
                std::cout << "Data After :" << _data << std::endl;
            } else {
                std::cerr << "ERROR IN HANDLE READ BODY" << std::endl;
                stop();
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
                    getSocket(),
                    boost::asio::buffer(_msg.c_str(), _msg.length()),
                    boost::bind(&ClientSocket::handle_write, shared_from_this(), boost::asio::placeholders::error)
                );
            } else {
                std::cerr << "ERROR IN HANDLE WRITE" << std::endl;
            }
        }

        void stop() final
        {
            boost::asio::post(getContext(),
                boost::bind(&ClientSocket::do_close, this)
            );
        }

        /* <- Private Methods -> */
    private:
        void do_close()
        {
            std::cout << "Client Socket Closed" << std::endl;
            getSocket().close();
        }

        /* <- Attributes -> */
    private:
        std::string _msg;
        static const size_t DATALENGTH = 3;
        char _data[DATALENGTH] = {0};
    };

}

#endif /* CPP_BABEL_2020_CLIENT_HPP */
