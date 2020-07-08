//
// Created by encorpluptit on 6/23/20.
//

#ifndef CPP_BABEL_2020_DEBUG_HPP
#define CPP_BABEL_2020_DEBUG_HPP

#ifdef _DEBUG_
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "StringFormat.tpp"

#define __F__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define dbg_local()                                                                             \
    std::cerr << std::format("[ %s ] - [ %s():%d ]", __F__, __func__, __LINE__) << std::endl;   \

#define dbg(x, ...)                                                         \
        dbg_local();                                                        \
        std::cerr << std::format(x"\n", __VA_ARGS__)                        \

#else

#define dbg_local()
#define dbg(x, ...)

#endif

#endif //CPP_BABEL_2020_DEBUG_HPP
