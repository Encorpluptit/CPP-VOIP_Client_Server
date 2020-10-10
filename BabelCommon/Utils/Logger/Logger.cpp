/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/9/20).
** File description:
** [Logger.cpp]: Source file for Logger feature.
*/

#include <iostream>
#include <ctime>
#include "Logger.hpp"

using namespace BabelUtils;

Logger::Logger(Logger::LogType type)
    : _type(type)
{
    initLogType();
    try {
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Logger::~Logger()
{
    logThis("Finished Logging");
    _logFile.close();
}

bool Logger::isOk() const
{
    return _ok;
}

void Logger::initLogType()
{
    switch (_type) {
        case ServerLog:
            _description = "Server";
            break;
        case ClientLog:
            _description = "Client";
            break;
        case UnknownLog:
            _description = "Unknown";
            break;
    }
}

void Logger::getTime()
{
    std::time_t rawtime;
    struct tm *timeinfo;

    if (std::time(&rawtime) == ((time_t) -1))
        return;
    if (!(timeinfo = std::localtime(&rawtime)))
        return;
    if (!strftime(_timeBuffer, FILENAME_MAX, "%H-%M-%S", timeinfo))
        return;
}

void Logger::logThis(const std::string &msg)
{
    if (!isOk())
        return;
    getTime();
    _logFile << "[ " << _description << " ] - " << _timeBuffer << " ==> " << msg << "\n";
}

void Logger::logThis(const std::shared_ptr<BabelNetwork::AResponse> &response, const std::string &msg)
{
    if (!isOk())
        return;
    getTime();
    if (msg.empty())
        _logFile << "[ " << _description << " ] - " << _timeBuffer << " ==> " << "Response :\n" << response << "\n";
    else
        _logFile << "[ " << _description << " ] - " << _timeBuffer << " ==> " << msg + "\n" << response << "\n";
}

void Logger::logThis(const BabelNetwork::NetworkInfos &infos, const std::string &msg)
{
    if (!isOk())
        return;
    getTime();
    _logFile << "[ " << _description << " ] - " << _timeBuffer << " ==> " << msg + "\n" << infos << "\n";
}
