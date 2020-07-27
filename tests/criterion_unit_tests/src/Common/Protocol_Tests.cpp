/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/10/20).
** File description:
** [Protocol_Tests.cpp]: Source file for Protocol_Tests.cpp feature.
*/

#include "tests_run.hpp"
#include "ConnectionResponse.hpp"

Test(Common, ConnectionResponse_1)
{
    BabelNetwork::ConnectionResponse test;

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_2)
{
    BabelNetwork::ConnectionResponse test;

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_3)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 84, .dataLength = 0
    };
    BabelNetwork::ConnectionResponse test(&hdr);

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_4)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 84, .dataLength = 0
    };
    BabelNetwork::ConnectionResponse test(&hdr);

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_5)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 0, .dataLength = 5
    };
    BabelNetwork::ConnectionResponse test(&hdr);

    ASSERT_UINT(test.getHeaderDataLength(), hdr.dataLength);
}

Test(Common, ConnectionResponse_6)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 0, .dataLength = 0
    };
    BabelNetwork::ConnectionResponse test(&hdr);

    ASSERT_BOOL(test.encode_header(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_UINT(test.getHeaderDataLength(), hdr.dataLength);
}

Test(Common, ConnectionResponse_7)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 40, .dataLength = 50
    };
    BabelNetwork::ConnectionResponse test(&hdr);

    ASSERT_BOOL(test.encode_header(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_UINT(test.getCode(), hdr.returnCode);
    ASSERT_UINT(test.getHeaderDataLength(), hdr.dataLength);
}

