/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/15/20).
** File description:
** [IThread.hpp]: Header file for IThread feature.
*/

#ifndef CPP_BABEL_2020_ITHREAD_HPP
#define CPP_BABEL_2020_ITHREAD_HPP

namespace BabelUtils {
    class IThread {

        /* <- Constructor - Destructor -> */
    public:
        virtual ~IThread() = 0;

        /* <- Methods -> */
    public:

        [[nodiscard]] virtual bool prepare() = 0;

        [[nodiscard]] virtual bool launch() = 0;

        [[nodiscard]] virtual bool run() = 0;

        [[nodiscard]] virtual bool stop() = 0;

    };

}

#endif /* CPP_BABEL_2020_ITHREAD_HPP */
