//
// Created by encorpluptit on 6/23/20.
//

#ifndef CPP_BABEL_2020_DEBUG_HPP
#define CPP_BABEL_2020_DEBUG_HPP

#ifdef _DEBUG_
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define __F__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define dbg_local()                                                         \
    dprintf(STDERR_FILENO, "[ %s ] - [ %s():%d ]", __F__, __func__, __LINE__)

#define dbg(x, ...) dbg_local(); dprintf(STDERR_FILENO, "\t"x"\n", __VA_ARGS__)

#else

#define __F__
#define dbg_local()
#define dbg(x, ...)

#endif


#endif //CPP_BABEL_2020_DEBUG_HPP
