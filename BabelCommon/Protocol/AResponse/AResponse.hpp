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



        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        explicit AResponse(const ResponseHeader *response);

        ~AResponse() override = default;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);

        /* <- Methods -> */
    public:
        [[nodiscard]] static std::shared_ptr<IResponse> getResponse(ResponseHeader *response, const char *data);

        [[nodiscard]] bool encode_header() override;

        [[nodiscard]] bool decode_header() override;

        [[nodiscard]] std::string serialize() const;

//        [[nodiscard]] bool isOk() override = 0;
//
//        void setOk() override = 0;
//
        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] uint16_t getCode() const;

        [[nodiscard]] uint32_t getHeaderDataLength() const;

        [[nodiscard]] virtual const std::string &getDescription() const = 0;

        [[nodiscard]] constexpr static size_t getResponseHeaderSize();

        [[nodiscard]] virtual size_t getResponseDataSize() = 0;

        [[nodiscard]] const char *getHeaderData() const;

        /* <- Attributes -> */
    protected:
        static const size_t ResponseHeaderSize = sizeof(ResponseHeader);
        ResponseHeader _header = {
            .returnCode = IResponse::ResponseCode::UnknownError,
            .dataLength = 0
        };
        char _headerData[ResponseHeaderSize] = {0};
    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const AResponse &response);
}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
