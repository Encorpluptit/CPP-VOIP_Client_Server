/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/10/20).
** File description:
** [Protocol_Tests.cpp]: Source file for Protocol_Tests.cpp feature.
*/

#include "tests_run.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

Test(Common, ConnectionResponse_1)
{
    ConnectionResponse test;

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_2)
{
    ConnectionResponse test;

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

Test(Common, ConnectionResponse_3)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 84,
        ._responseType = AResponse::ResponseType::Connection,
        ._dataInfosSize = 0
    };
    ConnectionResponse test(hdr);

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

Test(Common, ConnectionResponse_4)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 84,
        ._responseType = AResponse::ResponseType::Connection,
        ._dataInfosSize = 0,
    };
    ConnectionResponse test(hdr);

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

Test(Common, ConnectionResponse_5)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 0,
        ._responseType = AResponse::ResponseType::Connection,
        ._dataInfosSize = 5
    };
    ConnectionResponse test(hdr);

    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

Test(Common, ConnectionResponse_6)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 0,
        ._responseType = AResponse::ResponseType::Connection,
        ._dataInfosSize = 0
    };
    ConnectionResponse test(hdr);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

Test(Common, ConnectionResponse_7)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::Connection,
        ._dataInfosSize = 50
    };
    ConnectionResponse test(hdr);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_INT(test.getCode(), hdr._code);
    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Connection);
}

