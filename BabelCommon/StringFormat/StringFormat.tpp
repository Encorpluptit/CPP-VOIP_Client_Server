/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [StringFormat.hpp]: Template file for StringFormat feature.
*/

#ifndef CPP_BABEL_2020_STRINGFORMAT_TPP
#define CPP_BABEL_2020_STRINGFORMAT_TPP

#include <memory>
#include <string>
#include <stdexcept>

namespace std {
    template<typename ... Args>
    std::string format(const std::string &format, Args ... args)
    {
        // Extra space for '\0'
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
        if (size <= 0) { throw std::runtime_error("Error during formatting."); }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        // We don't want the '\0' inside
        return std::string(buf.get(), buf.get() + size - 1);
    }
}

#endif /* CPP_BABEL_2020_STRINGFORMAT_TPP */
