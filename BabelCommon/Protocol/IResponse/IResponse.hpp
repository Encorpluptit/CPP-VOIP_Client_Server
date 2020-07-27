/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [IResponse.hpp]: Header file for IResponse feature.
*/

#ifndef CPP_BABEL_2020_IRESPONSE_HPP
#define CPP_BABEL_2020_IRESPONSE_HPP

#include <memory>

namespace BabelNetwork {
    class IResponse {

        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            ConnectionOk = 100,
            LoginOk = 210,
            AccountCreated = 220,
            AccountDeleted = 230,
            UnknownError = 1000
        };

        /* <- Constructor - Destructor -> */
    public:
        IResponse() = default;

        virtual ~IResponse() = 0;

        /* <- Operators -> */
    public:

        /* <- Methods -> */
    public:
//        [[nodiscard]] static virtual std::unique_ptr<IResponse> getResponse(const std::string &input) = 0;

        [[nodiscard]] virtual bool encode_header() = 0;

        [[nodiscard]] virtual bool decode_header() = 0;

        [[nodiscard]] virtual bool decode_data() = 0;

        [[nodiscard]] virtual const char *getBodyData() const = 0;

        [[nodiscard]] virtual bool isOk() = 0;

        virtual void setOk() = 0;

    };

}

#endif /* CPP_BABEL_2020_IRESPONSE_HPP */
