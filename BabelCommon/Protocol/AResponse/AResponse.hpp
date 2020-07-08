/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
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
//            UnknownError = 1000
        };

        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        ~AResponse() override = default;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);

//        friend istream &operator>>( istream  &input, Distance &D );
            /* <- Methods -> */
    public:
        [[nodiscard]] std::unique_ptr<IResponse> getResponse(const std::string &input) override;

        [[nodiscard]] bool isOk() override = 0;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] int getCode() const;

        [[nodiscard]] const std::string &getDescription() const;

        [[nodiscard]] const std::string &getData() const;

        void setData(const std::string &data);

        /* <- Attributes -> */
    protected:
        IResponse::ResponseCode _code = IResponse::ResponseCode::UnknownError;
        std::string _description = "Connection between server and client";
        std::string _data;
    };

}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
