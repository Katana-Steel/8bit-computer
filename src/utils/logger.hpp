#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

class Logger {
public:
    enum class LogLevel {
        INFO,
        ERROR,
        WARNING
    };

    Logger(LogLevel level = LogLevel::INFO) : logLevel(level) {}

    void logInfo(const std::string& message) {
        if (logLevel <= LogLevel::INFO) {
            std::cout << "[INFO] " << message << std::endl;
        }
    }

    void logError(const std::string& message) {
        if (logLevel <= LogLevel::ERROR) {
            std::cout << "[ERROR] " << message << std::endl;
        }
    }

    void logWarning(const std::string& message) {
        if (logLevel <= LogLevel::WARNING) {
            std::cout << "[WARNING] " << message << std::endl;
        }
    }

    void setLogLevel(LogLevel level) {
        logLevel = level;
    }

private:
    LogLevel logLevel;
};

#endif // LOGGER_HPP