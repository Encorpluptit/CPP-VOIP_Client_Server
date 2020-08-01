/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.hpp]: Header file for AResponse feature.
*/

#ifndef CPP_BABEL_2020_ARESPONSE_HPP
#define CPP_BABEL_2020_ARESPONSE_HPP

#include <string>
#include <cstring>
#include <ostream>
#include <memory>

namespace BabelNetwork {

    class AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            ConnectionOk = 100,
            LoginOk = 210,
            AccountCreated = 220,
            AccountDeleted = 230,
            UnknownError = 1000
        };

        /* <- Class Enum -> */
    public:
        enum ResponseType {
            UnknownType,
            Connection,

        };

        /* <- Class Structure -> */
    public:
        using ResponseHeader = struct __attribute__((packed)) Response {
            uint16_t returnCode;
            ResponseType responseType;
            uint32_t dataLength;
        };
        static const size_t ResponseHeaderSize = sizeof(ResponseHeader);



        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        explicit AResponse(const ResponseHeader &headerResponse);

        AResponse(const AResponse &other) : AResponse(other._header)
        {
//            _header = other._header;
            memcpy(_headerData, other._headerData, sizeof(_headerData));
        }

        ~AResponse() = default;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);

        /* <- Methods -> */
    public:
        [[nodiscard]] static std::shared_ptr<AResponse> getResponse(const ResponseHeader &response) ;
//
//        [[nodiscard]] std::shared_ptr<AResponse> getResponse();
        [[nodiscard]] virtual std::shared_ptr<AResponse> getResponse() const = 0;

        [[nodiscard]] bool encode_header() noexcept;

        [[nodiscard]] bool decode_header() noexcept;

        [[nodiscard]] virtual bool encode_data() noexcept = 0;

        [[nodiscard]] virtual bool decode_data() noexcept = 0;

        [[nodiscard]] std::string serialize() const;

        [[nodiscard]] virtual bool isOk() noexcept = 0;

        virtual void setOk() noexcept = 0;

        /* <- Getters / Setters -> */
    public:

        [[nodiscard]] uint16_t getCode() const noexcept;

        [[nodiscard]] uint32_t getHeaderDataLength() const noexcept;

        [[nodiscard]] virtual const std::string &getDescription() const noexcept = 0;

//        [[nodiscard]] constexpr static size_t getHeaderSize();
        [[nodiscard]] constexpr static size_t getHeaderSize() { return ResponseHeaderSize;};

        [[nodiscard]] char *getHeaderData();

        [[nodiscard]] virtual char *getBodyData() noexcept = 0;

        [[nodiscard]] virtual char *getBody() noexcept = 0;

        [[nodiscard]] const ResponseType &getResponseType() const;

        /* <- Attributes -> */
    protected:
        ResponseHeader _header = {
            .returnCode = AResponse::ResponseCode::UnknownError,
            .responseType = UnknownType,
            .dataLength = 0
        };
        char _headerData[ResponseHeaderSize] = {0};

    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const AResponse &response);
}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
