/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/10/20).
** File description:
** [Protocol_Tests.cpp]: Header file for Protocol_Tests.cpp feature.
*/

#include "tests_run.hpp"
#include "ConnectionResponse.hpp"

Test(Common, ConnectionResponse1)
{
    BabelNetwork::ConnectionResponse test;

    ASSERT_BOOL(test.isOk(), false);
}