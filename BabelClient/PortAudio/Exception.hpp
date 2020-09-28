/*
** EPITECH PROJECT, 2020
** Exception.hpp
** File description:
** Exception.hpp
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(std::string const &str) { message = str; }

    std::string what() { return (message); }

private:
    std::string message;
};
