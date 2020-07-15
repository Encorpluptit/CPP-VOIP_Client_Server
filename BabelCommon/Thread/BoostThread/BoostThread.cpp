/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/15/20).
** File description:
** [BoostThread.cpp]: Source file for BoostThread feature.
*/

#include "BoostThread.hpp"

using namespace BabelUtils;


bool BoostThread::prepare()
{
    return false;
}

bool BoostThread::launch()
{
    return false;
}

bool BoostThread::run()
{
    return false;
}

bool BoostThread::stop()
{
    _thread.join();
}
