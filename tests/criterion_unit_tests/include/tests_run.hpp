/*
** EPITECH PROJECT, 2019
** Any Project
** File description:
** Header for Unit Test using criterion.
*/

#ifndef __TESTS_RUN_H__
#define __TESTS_RUN_H__

#include <criterion/criterion.h>
#include <criterion/redirect.h>

static inline void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

#define ASSERT_INT(actual, expected) cr_assert_eq(actual, expected, "Expected %d, got %d\n", expected, actual)
#define EXPECT_INT(actual, expected) cr_expect_eq(actual, expected, "Expected %d, got %d\n", expected, actual)
#define ASSERT_UINT(actual, expected) cr_assert_eq(actual, expected, "Expected %u, got %u\n", expected, actual)
#define EXPECT_UINT(actual, expected) cr_expect_eq(actual, expected, "Expected %u, got %u\n", expected, actual)
#define ASSERT_SIZET(actual, expected) cr_assert_eq(actual, expected, "Expected %zu, got %zu\n", expected, actual)
#define EXPECT_SIZET(actual, expected) cr_expect_eq(actual, expected, "Expected %zu, got %zu\n", expected, actual)
#define ASSERT_BOOL(actual, expected) cr_assert_eq(actual, expected, "Expected %s, got %s\n", expected ? "true" : "false", actual ? "true" : "false")
#define EXPECT_BOOL(actual, expected) cr_expect_eq(actual, expected, "Expected %s, got %s\n", expected ? "true" : "false", actual ? "true" : "false")

#endif /* __TESTS_RUN_H__ */
