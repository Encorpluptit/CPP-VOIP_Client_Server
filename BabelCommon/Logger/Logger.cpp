/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/9/20).
** File description:
** [Logger.cpp]: Source file for Logger feature.
*/

#include <iostream>
#include <ctime>
#include "Logger.hpp"
#include "LoggerError.hpp"

using namespace BabelUtils;

Logger::Logger(Logger::LogType type)
{
    initLogType(type);
    try {
        std::filesystem::path tmpPath = createLogDirectories();
        createLogFile(tmpPath);
        _ok = true;
    } catch (const LoggerError &e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Logger::~Logger()
{
    std::cerr << "Finished Logging" << std::endl;
    _logFile.close();
}

bool Logger::isOk() const
{
    return _ok;
}

void Logger::initLogType(Logger::LogType type)
{
    switch (type) {
        case ServerLog:
            _description = "Server";
            _type = ServerLog;
            break;
        case ClientLog:
            _description = "Client";
            _type = ClientLog;
            break;
        default:
            _type = UnknownLog;
            break;
    }
}

std::filesystem::path Logger::createLogDirectories()
{
    const std::string LogDir("BabelLogs");
    const std::string TargetLogDir("Babel" + _description + "Log");
    const std::filesystem::path current_path(std::filesystem::current_path());
    std::filesystem::path tmpPath(current_path);

    tmpPath /= LogDir;
    std::filesystem::create_directory(tmpPath);
    tmpPath /= TargetLogDir;
    std::filesystem::create_directory(tmpPath);
    return tmpPath;
}

void Logger::createLogFile(std::filesystem::path filePath)
{
    time_t rawtime;
    struct tm *timeinfo;
    size_t sz = FILENAME_MAX - filePath.string().size();
    char fileName[FILENAME_MAX] = {0};

    if (time(&rawtime) == ((time_t) -1) || !(timeinfo = localtime(&rawtime))
        || !strftime(fileName, sz, "%Y-%m-%d_%H-%M-%S.log", timeinfo)) {
        filePath /= std::string("Log_File.log");
        _logFile = std::ofstream(filePath.string());
        return;
    }
    filePath /= std::string(fileName);
    _logFile = std::ofstream(filePath.string());
}
