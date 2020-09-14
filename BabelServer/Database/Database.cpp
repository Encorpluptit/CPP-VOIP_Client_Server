/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 9/7/20).
** File description:
** [Database.cpp]: Source file for Database feature.
*/

#include <sqlite_orm.h>
#include "User.hpp"
#include "Database.hpp"

using namespace BabelServer;

Database::Database()
{
    using namespace sqlite_orm;
    auto storage = make_storage("db.sqlite",
        make_table("users",
            make_column("id", &User::id, autoincrement(), primary_key()),
            make_column("first_name", &User::login),
            make_column("last_name", &User::password)
        )/*,
            */
    );
}
