/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/4/20).
** File description:
** [ARunnable.h]: Header file for ARunnable feature.
*/

#ifndef CPP_BABEL_2020_ARUNNABLE_H
#define CPP_BABEL_2020_ARUNNABLE_H

#include "IRunnable.hpp"

namespace BabelUtils {
    class ARunnable : virtual public IRunnable {

        /* <- Constructor - Destructor -> */
    public:
        ~ARunnable() override = default;

        /* <- Public Methods -> */
    public:
        [[nodiscard]] bool isReady() const override { return _ready; };

        void setReady() override { _ready = true; };

        void setNotReady() override { _ready = false; };

        /* <- Attributes -> */
    protected:
        bool _ready = false;
    };

}

#endif /* CPP_BABEL_2020_ARUNNABLE_H */
