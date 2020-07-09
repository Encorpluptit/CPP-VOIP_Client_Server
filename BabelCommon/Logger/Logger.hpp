/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/9/20).
** File description:
** [Logger.hpp]: Header file for Logger feature.
*/

#ifndef CPP_BABEL_2020_LOGGER_HPP
#define CPP_BABEL_2020_LOGGER_HPP

#include <fstream>
#include <filesystem>
#include "LoggerError.hpp"

namespace BabelUtils {
    class Logger {

        /* <- Class Enum -> */
    public:
        enum LogType {
            ServerLog,
            ClientLog,
            UnknownLog
        };

        /* <- Constructor - Destructor -> */
    public:
        explicit Logger(Logger::LogType type);
        ~Logger();


        /* <- Methods -> */
    public:
        void logThis(const std::string &data);

    private:
        void initLogType(Logger::LogType type);
        std::filesystem::path createLogDirectories();
        void createLogFile(std::filesystem::path filePath);

        /* <- Getters / Setters -> */
    public:
        bool isOk();

        /* <- Attributes -> */
    private:
        std::ofstream _logFile;
        bool _ok = false;
        LogType _type = UnknownLog;
        std::string _description;
//        std::filesystem::path;
    };
}

#endif /* CPP_BABEL_2020_LOGGER_HPP */
