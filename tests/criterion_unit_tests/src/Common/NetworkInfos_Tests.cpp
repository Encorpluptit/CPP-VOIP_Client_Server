/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) Encorpluptit on 7/12/20).
** File description:
** [NetworkInfos_Tests.cpp]: Source file for NetworkInfos_Tests feature.
*/

#include "tests_run.hpp"
#include "NetworkInfos.hpp"
#include "NetworkError.hpp"

Test(Common, NetworkInfosClass_1)
{
    char const *ip = "127.0.0.1";
    BabelNetwork::NetworkInfos test(ip);
    int portExp = atoi(DEFAULT_PORT());

    cr_assert_str_eq(test.getIp().c_str(), ip);
    ASSERT_INT(test.getPort(), portExp);
}

Test(Common, NetworkInfosClass_2)
{
    char const *ip = "127.0.0.1";
    char const *port = "8080";
    BabelNetwork::NetworkInfos test(ip, port);
    int portExp = atoi(port);

    cr_assert_str_eq(test.getIp().c_str(), ip);
    cr_assert_str_eq(test.getPortStr().c_str(), port);
    ASSERT_INT(test.getPort(), portExp);
}

Test(Common, NetworkInfosClass_3)
{
    char const *ip = "192.0.0.1";
    char const *port = "5555";
    BabelNetwork::NetworkInfos test(ip, port);
    int portExp = atoi(port);

    cr_assert_str_eq(test.getIp().c_str(), ip);
    cr_assert_str_eq(test.getPortStr().c_str(), port);
    ASSERT_INT(test.getPort(), portExp);
}

Test(Common, NetworkInfosClass_4)
{
    char const *ip = "192.0.0.1";
    char const *port = "aaaa";

    cr_assert_throw(
        BabelNetwork::NetworkInfos test(ip, port);,
        BabelErrors::NetworkError
    )
}
