/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.hpp]: Header file for ConnectionResponse feature.
*/

#ifndef CPP_BABEL_2020_CONNECTIONRESPONSE_HPP
#define CPP_BABEL_2020_CONNECTIONRESPONSE_HPP

#include "AResponse.hpp"

namespace BabelNetwork {
    class ConnectionResponse final : virtual public AResponse {
        /* <- Class Structure -> */
    private:
        enum DataSize {
            Login = 128,
            Password = 128
        };

        /* <- Class Structure -> */
    public:
        using ConnectionData = struct __attribute__((packed)) ConnectionDataStruct {
            char login[DataSize::Login];
            char password[DataSize::Password];
        };
        static const size_t _data_size = sizeof(ConnectionData);

        /* <- Constructor - Destructor -> */
    public:
        ConnectionResponse() {
            _header.responseType = Connection;
            _header.dataLength = sizeof(ConnectionData);

            //TODO: remove
            strcat(_data.login, "lol");
        };

        explicit ConnectionResponse(const ResponseHeader &headerResponse);

        ConnectionResponse(const ConnectionResponse &other) : AResponse(other)
        {
            memcpy(_body_data, other._body_data, sizeof(_body_data));
            memcpy(&_data, &other._data, sizeof(_data));
        }

        ~ConnectionResponse() = default;

        /* <- Methods -> */
    public:
        [[nodiscard]] bool isOk() noexcept final;

        void setOk() noexcept final;

        [[nodiscard]] bool encode_data() noexcept final;

        [[nodiscard]] bool decode_data() noexcept final;

        [[nodiscard]] char *getBodyData() noexcept final;

        [[nodiscard]] char *getBody() noexcept final;

        [[nodiscard]] std::shared_ptr<AResponse> getResponse() const final;

//        [[nodiscard]] const char *getResponseType() const noexcept final;


        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::string &getDescription() const noexcept final;

    private:
        const std::string _description = "Connection between server and client";
        char _body_data[_data_size]{};
        ConnectionData _data{};
    };
}

#endif /* CPP_BABEL_2020_CONNECTIONRESPONSE_HPP */
