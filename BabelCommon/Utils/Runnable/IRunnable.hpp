/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [IRunnable.hpp]: Header file for IRunnable feature.
*/

#ifndef CPP_BABEL_2020_IRUNNABLE_HPP
#define CPP_BABEL_2020_IRUNNABLE_HPP

#include "NetworkInfos.hpp"
#include "AResponse.hpp"

namespace BabelUtils {
    class IRunnable {

        /* <- Constructor - Destructor -> */
    public:
        virtual ~IRunnable() = default;

        /* <- Public Methods -> */
    public:
        virtual void start() = 0;

        virtual void stop() = 0;

        [[nodiscard]] virtual bool isReady() const = 0;

        virtual void setReady() = 0;

        virtual void setNotReady() = 0;
    };

}

#endif /* CPP_BABEL_2020_IRUNNABLE_HPP */
