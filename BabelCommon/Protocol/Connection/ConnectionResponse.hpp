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

        /* <- Constructor - Destructor -> */
    public:
        ConnectionResponse();

        ~ConnectionResponse() override = default;

        /* <- Methods -> */
    public:
        [[nodiscard]] bool isOk() final;

        void setOk() final;
    };
}

#endif /* CPP_BABEL_2020_CONNECTIONRESPONSE_HPP */
