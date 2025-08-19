#pragma once 
#include <string>

namespace lwslog {
    enum class LogLevel {
    TRACE,   // Detail debug information
    DEBUG,   // Debug messages
    INFO,    // information messages
    WARN,    // warnings
    ERROR,   // errors
    FATAL    // fatal errors
};
inline std::string toString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

}