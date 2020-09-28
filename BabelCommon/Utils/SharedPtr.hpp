/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [SharedPtr.hpp]: Header file for SharedPtrpp feature.
*/

#ifndef CPP_BABEL_2020_SHAREDPTR_HPP
#define CPP_BABEL_2020_SHAREDPTR_HPP

#include <boost/smart_ptr/make_shared.hpp>
#include "boost/shared_ptr.hpp"

namespace BabelUtils {
    template<typename T>
    using SharedPtr = boost::shared_ptr<T>;

    template<typename T, typename ... Args>
    SharedPtr<T> makeSharedPtr(Args &... args)
    {
        return boost::make_shared<T>(args...);
    }
}

#endif /* CPP_BABEL_2020_SHAREDPTR_HPP */
