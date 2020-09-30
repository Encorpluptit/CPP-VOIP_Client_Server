//
// Created by encorpluptit on 9/30/20.
//

#ifndef CPP_BABEL_2020_SERVERERROR_H
#define CPP_BABEL_2020_SERVERERROR_H

#include "BabelError.hpp"

namespace BabelServer {
    class ServerError : public BabelErrors::BabelError {
        /* <- Constructor - Destructor -> */
    public:
        explicit ServerError(std::string const &msg) : BabelErrors::BabelError(msg) {}
    };
}

#endif //CPP_BABEL_2020_SERVERERROR_H
