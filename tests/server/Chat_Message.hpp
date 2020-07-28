/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [Chat_message.hpp]: Header file for Chat_messagepp feature.
*/

#ifndef CPP_BABEL_2020_CHAT_MESSAGE_HPP
#define CPP_BABEL_2020_CHAT_MESSAGE_HPP
//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message {
public:
    enum {
        header_length = 4
    };
    enum {
        max_body_length = 512
    };

    chat_message()
        : body_length_(0)
    {
    }

    [[nodiscard]] const char *data() const
    {
        return data_;
    }

    char *data()
    {
        return data_;
    }

    [[nodiscard]] size_t length() const
    {
        return header_length + body_length_;
    }

    [[nodiscard]] const char *body() const
    {
        return data_ + header_length;
    }

    char *body()
    {
        return data_ + header_length;
    }

    [[nodiscard]] size_t body_length() const
    {
        return body_length_;
    }

    void body_length(size_t new_length)
    {
        body_length_ = new_length;
        if (body_length_ > max_body_length)
            body_length_ = max_body_length;
    }

    bool decode_header()
    {
        using namespace std; // For strncat and atoi.
        char header[header_length + 1] = "";
        strncat(header, data_, header_length);
        body_length_ = atoi(header);
        if (body_length_ > max_body_length) {
            body_length_ = 0;
            return false;
        }
        return true;
    }

    void encode_header()
    {
        using namespace std; // For sprintf and memcpy.
        char header[header_length + 1] = "";
        sprintf(header, "%4d", static_cast<int>(body_length_));
        memcpy(data_, header, header_length);
    }

private:
    char data_[header_length + max_body_length] = {0};
    size_t body_length_;
};

#endif // CHAT_MESSAGE_HPP

#endif /* CPP_BABEL_2020_CHAT_MESSAGE_HPP */
