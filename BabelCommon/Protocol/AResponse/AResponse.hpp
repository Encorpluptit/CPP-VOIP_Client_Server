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

    class AResponse : virtual public IResponse {

        /* <- Class Structure -> */
    public:
        using ResponseHeader = struct __attribute__((packed)) Response {
            uint16_t returnCode;
            uint32_t dataLength;
        };
        size_t ResponseHeaderSize = sizeof(ResponseHeader);



        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        explicit AResponse(const ResponseHeader *response, const char *data);

        ~AResponse() override = default;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);

//        friend istream &operator>>( istream  &input, Distance &D );
        /* <- Methods -> */
    public:
        [[nodiscard]] std::unique_ptr<IResponse> getResponse(ResponseHeader *response, const char *data);

        [[nodiscard]] bool isOk() override = 0;

        [[nodiscard]] std::string serialize() const;

        void setOk() override = 0;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] uint16_t getCode() const;

        [[nodiscard]] const std::string &getDescription() const;

        [[nodiscard]] const std::string &getData() const;

        void setData(const std::string &data);

        /* <- Attributes -> */
    protected:
        uint16_t _code = IResponse::ResponseCode::UnknownError;
        const std::string _description;
        std::string _data;
    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const AResponse &response);

}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
