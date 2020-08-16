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
#include "StringFormat.tpp"
#include "AResponse.hpp"

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


        /* <- Public Methods -> */
    public:
        template<typename ... Args>
        void logThis(const std::string &fmt, Args ... args)
        {
            if (!isOk())
                return;
            getTime();
            _logFile << "[ " << _description << " ]  - " << _timeBuffer << " ==> " << format(fmt, args...) + "\n";
        }

        void logThis(const std::string &msg);

        void logThis(const BabelNetwork::AResponse &response, const std::string &msg = "");

        /* <- Private Methods -> */
    private:
        void getTime();

        void initLogType();

        std::filesystem::path createLogDirectories();

        void createLogFile(std::filesystem::path filePath);

        /* <- Getters / Setters -> */
    private:
        bool isOk() const;

        /* <- Attributes -> */
    private:
        std::ofstream _logFile;
        bool _ok = false;
        LogType _type = UnknownLog;
        std::string _description;
        char _timeBuffer[FILENAME_MAX] = {0};
    };
}

#endif /* CPP_BABEL_2020_LOGGER_HPP */