/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Header file for Database feature.
*/

#ifndef CPP_BABEL_2020_DATABASE_HPP
#define CPP_BABEL_2020_DATABASE_HPP

namespace BabelServer {
    class Database {
        /* <- Constructor - Destructor -> */
    public:
        explicit Database();

        /* <- Public Methods -> */
    public:
        /* <- Private Methods -> */
    private:
        void lock() { _mtx.lock(); }

        void unlock() { _mtx.unlock(); }

        /* <- Attributes -> */
    private:
        std::mutex _mtx;

    };

}

#endif //CPP_BABEL_2020_DATABASE_HPP
