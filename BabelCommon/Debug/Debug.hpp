/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Server.cpp]: Header file for Server feature.
*/
#ifndef CPP_BABEL_2020_DEBUG_HPP
#define CPP_BABEL_2020_DEBUG_HPP

#ifdef _DEBUG_

#include "StringFormat.tpp"

#define __F__ (std::string(__FILE__).substr(std::string(__FILE__).find_last_of('/')).c_str() + 1)

#define dbg_local()                                                                             \
    std::cerr << std::format("<-- START DEBUG -->\n[ %s ] - [ %s():%d ]",       \
        __F__, __func__, __LINE__) << std::endl;                                \

#define dbg(x, ...)                                                             \
    dbg_local();                                                                \
    std::cerr << std::format(x"\n<-- END DEBUG -->\n", __VA_ARGS__);            \

#else

#define dbg_local()
#define dbg(x, ...)

#endif /* _DEBUG_ */

#endif /* CPP_BABEL_2020_DEBUG_HPP */
