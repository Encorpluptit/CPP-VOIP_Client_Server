/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [SharedPtr.hpp]: Header file for SharedPtrpp feature.
*/

#ifndef CPP_BABEL_2020_SHAREDPTR_HPP
#define CPP_BABEL_2020_SHAREDPTR_HPP

#include "boost/shared_ptr.hpp"

namespace BabelUtils {
    template<typename T>
    using SharedPtr = boost::shared_ptr<T>;
}

#endif /* CPP_BABEL_2020_SHAREDPTR_HPP */
