//
// Created by encorpluptit on 9/30/20.
//

#ifndef CPP_BABEL_2020_DATABASEERROR_HPP
#define CPP_BABEL_2020_DATABASEERROR_HPP

#include "ServerError.hpp"

namespace BabelServer {
    class DatabseError : public ServerError {
        /* <- Constructor - Destructor -> */
    public:
        explicit DatabseError(std::string const &msg) : ServerError(msg) {}
    };
}

#endif //CPP_BABEL_2020_DATABASEERROR_HPP
