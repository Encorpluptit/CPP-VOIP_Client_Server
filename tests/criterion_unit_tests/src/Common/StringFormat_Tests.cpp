/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/10/20).
** File description:
** [StringFormat_Tests.cpp]: Header file for StringFormat_Tests.cpp feature.
*/

#include "tests_run.hpp"
#include "StringFormat.tpp"

Test(Common, StringFormatTest1)
{
    int value = 5;
    const char *exp = "value = 5";
    std::string res = std::format("value = %d", value);

    cr_assert_str_eq(res.c_str(), exp);
}