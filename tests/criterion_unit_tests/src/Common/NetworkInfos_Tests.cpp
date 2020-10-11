/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) Encorpluptit on 7/12/20).
** File description:
** [NetworkInfos_Tests.cpp]: Source file for NetworkInfos_Tests feature.
*/

#include <iostream>
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

Test(Common, NetworkInfosClass_5)
{
    char const *ip = "192.0.0.1";
    char const *port = "4999";

    cr_assert_throw(
        BabelNetwork::NetworkInfos test(ip, port);,
        BabelErrors::NetworkError
    )
}

Test(Common, NetworkInfosClass_6)
{
    char const *ip = "192.0.0.1";
    char const *port = "5555";
    BabelNetwork::NetworkInfos test_1(ip, port);
    BabelNetwork::NetworkInfos test_2(ip, port);

    ASSERT_BOOL(test_1 == test_2, true);
}

Test(Common, NetworkInfosClass_print, .init=redirect_all_std)
{
    char const *ip = "192.0.0.1";
    char const *port = "5555";
    BabelNetwork::NetworkInfos test(ip, port);
    std::cout << test << std::endl;
    cr_assert_stdout_eq_str("Connexion at 192.0.0.1 address and port 5555\n");
}

Test(Common, NetworkInfosClass_7)
{
    char const *ip = "192.0.0.1";
    char const *portStr = "5555";
    uint16_t port = 5556;
    BabelNetwork::NetworkInfos test(ip, portStr);

    test.setPort(port);
    cr_assert_str_eq(test.getIp().c_str(), ip);
    ASSERT_INT(test.getPort(), port);
}

Test(Common, NetworkInfosClass_8)
{
    char const *ip_1 = "192.0.0.1";
    char const *ip_2 = "192.0.0.2";
    char const *portStr = "5555";
    BabelNetwork::NetworkInfos test(ip_1, portStr);
    int portExp = atoi(portStr);

    test.setIp(ip_2);
    cr_assert_str_eq(test.getIp().c_str(), ip_2);
    ASSERT_INT(test.getPort(), portExp);
}
