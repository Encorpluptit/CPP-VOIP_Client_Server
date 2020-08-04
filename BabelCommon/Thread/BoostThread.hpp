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

//    template<typename T>
    class BoostThread final : virtual public AThread {

        /* <- Constructor - Destructor -> */
    public:
//        BoostThread() : AThread<boost::thread>() {};


        template<typename ... Args>
        explicit BoostThread(Args ... args) : _thread(args ...) {};

//        template<typename ... Args>
//        explicit BoostThread(Args ... args) : AThread<boost::thread>(args ...) {};

        ~BoostThread() final = default;
//        ~BoostThread() final {
//            stop();
//        };


        /* <- Methods -> */
    public:
        void start() final {};

        void waitExecution() final {_thread.join();}

        void stop() final {waitExecution();};

        /* <- Attributes -> */
    private:
        boost::thread _thread;
    };
}

#endif /* CPP_BABEL_2020_BOOSTTHREAD_HPP */
