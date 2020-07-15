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

    class BoostThread final : virtual public AThread {

        /* <- Constructor - Destructor -> */
    public:
//        BoostThread(int nb_threads);

        ~BoostThread() final = default;


        /* <- Methods -> */
    public:

        [[nodiscard]] bool prepare() final;

        [[nodiscard]] bool launch() final;

        [[nodiscard]] bool run() final;

        [[nodiscard]] bool stop() final;

        /* <- Attributes -> */
    private:
        T _handler;
        boost::thread _thread;
    };

}

#endif /* CPP_BABEL_2020_BOOSTTHREAD_HPP */
