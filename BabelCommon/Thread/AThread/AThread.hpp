/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/15/20).
** File description:
** [AThread.hpp]: Header file for AThread feature.
*/

#ifndef CPP_BABEL_2020_ATHREAD_HPP
#define CPP_BABEL_2020_ATHREAD_HPP


#include "IThread.hpp"

namespace BabelUtils {

    template<typename T>
    class AThread : virtual public IThread {

        /* <- Constructor - Destructor -> */
    public:
        explicit AThread(int nb_threads = 10) : _nb_threads(nb_threads) {};

        ~AThread() override = default;

        /* <- Methods -> */
    public:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] int getNbThreads() const { return _nb_threads; };

        void setNbThreads(int nbThreads) { _nb_threads = nbThreads; };

        /* <- Attributes -> */
    protected:
//        T _handler;
        int _nb_threads;
    };

}


#endif /* CPP_BABEL_2020_ATHREAD_HPP */
