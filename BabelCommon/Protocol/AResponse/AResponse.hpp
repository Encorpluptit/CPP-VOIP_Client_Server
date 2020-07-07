/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20.
** File description:
** [AResponse.hpp]: Header file for AResponse feature.
*/

#ifndef CPP_BABEL_2020_ARESPONSE_HPP
#define CPP_BABEL_2020_ARESPONSE_HPP

#include <string>
#include <ostream>
#include "IResponse.hpp"

namespace BabelNetwork {

    class AResponse : public IResponse {

        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            UnknownError = 1000
        };

        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        ~AResponse() override = 0;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);


        /* <- Methods -> */
    public:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] int getCode() const;

        [[nodiscard]] const std::string &getDescription() const;


        /* <- Attributes -> */
    protected:
        int _code = ResponseCode::UnknownError;
        std::string _description;
    };

}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
