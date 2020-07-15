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

#define DEBUG_INFOS() __F__, __func__, __LINE__

#define dbg_local()                                                                             \
    std::cerr << BabelUtils::format("<-- START DEBUG -->\n[ %s ] - [ %s():%d ]", DEBUG_INFOS()) << std::endl;

#define dbg(x, ...)                                                             \
    dbg_local();                                                                \
    std::cerr << BabelUtils::format(x"\n<-- END DEBUG -->\n", __VA_ARGS__);     \

#else

#define DEBUG_INFOS() ""
#define dbg_local()
#define dbg(x, ...)

#endif /* _DEBUG_ */

#endif /* CPP_BABEL_2020_DEBUG_HPP */
