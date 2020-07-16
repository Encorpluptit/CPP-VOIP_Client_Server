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
    class ConnectionResponse final : public AResponse {

        /* <- Constructor - Destructor -> */
    public:
        ConnectionResponse() = default;

        ConnectionResponse(const ResponseHeader *response, const char *data);

        ~ConnectionResponse() override = default;

        /* <- Methods -> */
    public:
        [[nodiscard]] bool isOk() final;

        void setOk() final;

    private:
        const std::string _description = "Connection between server and client";
    };
}

#endif /* CPP_BABEL_2020_CONNECTIONRESPONSE_HPP */
