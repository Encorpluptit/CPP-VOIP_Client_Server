/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/15/20).
** File description:
** [AThread.hpp]: Header file for AThread feature.
*/

#ifndef CPP_BABEL_2020_ATHREAD_HPP
#define CPP_BABEL_2020_ATHREAD_HPP

#include "Runnable/ARunnable.hpp"

namespace BabelUtils {

    class AThread : virtual public ARunnable {

        /* <- Constructor - Destructor -> */
    public:
        AThread() = default;

        ~AThread() override = default;

        /* <- Methods -> */
    public:
        virtual void waitExecution() = 0;
    };

}


#endif /* CPP_BABEL_2020_ATHREAD_HPP */
