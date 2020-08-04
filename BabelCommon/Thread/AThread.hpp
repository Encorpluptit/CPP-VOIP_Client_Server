/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/15/20).
** File description:
** [AThread.hpp]: Header file for AThread feature.
*/

#ifndef CPP_BABEL_2020_ATHREAD_HPP
#define CPP_BABEL_2020_ATHREAD_HPP

#include <functional>

namespace BabelUtils {

    class AThread {

        /* <- Constructor - Destructor -> */
    public:
        AThread() = default;
//
//        template<typename ... Args>
//        AThread(Args ... args) = 0;

        virtual ~AThread() = default;

        /* <- Methods -> */
    public:

        virtual void run() = 0;

        virtual void stop() = 0;

        virtual void waitExecution() = 0;
    };

}


#endif /* CPP_BABEL_2020_ATHREAD_HPP */
