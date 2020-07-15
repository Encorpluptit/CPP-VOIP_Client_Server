/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/15/20).
** File description:
** [BoostThread.hpp]: Header file for BoostThread feature.
*/

#ifndef CPP_BABEL_2020_BOOSTTHREAD_HPP
#define CPP_BABEL_2020_BOOSTTHREAD_HPP

#include <boost/thread.hpp>
#include "AThread.hpp"

namespace BabelUtils {

//    template<typename T, typename H, typename ... Args>
    template<typename T, typename H>
    class BoostThread final : virtual public AThread<T> {

        /* <- Constructor - Destructor -> */
    public:
        BoostThread(int nb_threads, H handler): AThread<T>(nb_threads), _handler(handler) {};

        ~BoostThread() final = default;


        /* <- Methods -> */
    public:

        [[nodiscard]] bool prepare() final
        {
            return false;
        };

        [[nodiscard]] bool launch() final
        {
            return false;
        };

        template<typename ... Args>
        [[nodiscard]] bool setHandler(H handler, Args ... args)
        {
            boost::bind(_handler, args ...);
            return false;
        };

        [[nodiscard]] bool run() final
        {
            return false;
        };

        [[nodiscard]] bool stop() final
        {
            return false;
        };

        /* <- Attributes -> */
    private:
        H _handler;
        T _thread;
    };

}

#endif /* CPP_BABEL_2020_BOOSTTHREAD_HPP */
