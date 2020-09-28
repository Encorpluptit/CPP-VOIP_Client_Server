/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/27/20).
** File description:
** [AsioClientSocket.hpp]: Header file for AsioClientSocket feature.
*/

#ifndef CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP
#define CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP

#include <boost/asio.hpp>
#include "ClientSocket.hpp"

namespace BabelNetwork {
    using namespace boost::asio;

    class AsioClientSocket final
        : virtual public ClientSocket,
          public boost::enable_shared_from_this<AsioClientSocket> {

        /* <- Class Enum -> */
    public:
        enum SocketHandler {
            Server,
            Client
        };

        /* <- Constructor - Destructor -> */
    public:
        explicit AsioClientSocket(
            const std::string &address,
            const std::string &port,
            BabelUtils::Logger &logger,
            io_context &context,
            SocketHandler handlerType
        );

        ~AsioClientSocket() final;

        /* <- Public Methods -> */
    public:

        void start() final;

        void stop() final
        {
            if (getHandler() == SocketHandler::Client)
                _context.stop();
            _socket.close();
            setNotReady();
        };

        bool sendResponse(const BabelNetwork::AResponse &response) final;

        bool sendResponse(const std::shared_ptr<AResponse> &response) final;

        void connect() override;

        [[nodiscard]] std::string describe() final;

        /* <- Private Methods -> */
    private:

        void handle_connect(const boost::system::error_code &error);

        void read_header();

        void read_data_infos(const boost::system::error_code &error);

        void read_data(const boost::system::error_code &error);

        void queue_read_response(const boost::system::error_code &error);

        void do_write(bool write_in_progress);

        void handle_write(const boost::system::error_code &error);

        void handle_error(const std::string &msg, const boost::system::error_code &error);


        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] ip::tcp::socket &getSocket() { return _socket; }

        [[nodiscard]] SocketHandler getHandler() const { return _handler; }

        [[nodiscard]] io_context &getContext() const { return const_cast<io_context &>(_context);}

        [[nodiscard]] std::string getIp() final;

        [[nodiscard]] std::string getPort() final;


        /* <- Attributes -> */
    private:
        io_context &_context;
        ip::tcp::socket _socket;
        ip::tcp::resolver::results_type _endpoints;
        SocketHandler _handler;
    };

}

#endif /* CPP_BABEL_2020_ASIOCLIENTSOCKET_HPP */
