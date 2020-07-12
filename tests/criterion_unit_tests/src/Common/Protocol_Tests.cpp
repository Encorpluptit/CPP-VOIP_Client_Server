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
    const char *data = "";
    BabelNetwork::ConnectionResponse test(&hdr, data);

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, ConnectionResponse_4)
{
    static const BabelNetwork::AResponse::ResponseHeader hdr = {
        .returnCode = 84, .dataLength = 0
    };
    const char *data = nullptr;
    BabelNetwork::ConnectionResponse test(&hdr, data);

    ASSERT_BOOL(test.isOk(), false);
}

