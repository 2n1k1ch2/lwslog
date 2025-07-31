#pragma once 
#include "FreeLoggerImpl.hpp"
#include "FixedLoggerImpl.hpp"
#include <memory>
#include <string>
#include <ostream>
enum class LogLevel {
    TRACE,   // Detail debug information
    DEBUG,   // Debug messages
    INFO,    // information messages
    WARN,    // warnings
    ERROR,   // errors
    FATAL    // fatal errors
};

class ILoggerImpl {
public:
    virtual ~ILoggerImpl() = default;

    virtual void Flush() = 0;

    template<typename T>
    ILoggerImpl& operator<<(const T& val) {
        Append(val);
        return *this;
    }

protected:
    virtual void Append(const std::string& str) = 0;

    template<typename T>
    void Append(const T& val) {
        std::ostringstream oss;
        oss << val;
        Append(oss.str());
    }
};

class Logger {
private:
    std::unique_ptr<ILoggerImpl> impl_;
public:
    Logger() : impl_(std::make_unique<FreeLoggerImpl>()) {}

    Logger(LogLevel level) : impl_(std::make_unique<FixedLoggerImpl>(level)) {}

    template<typename T>
    Logger& operator<<(const T& val) {
        (*impl_) << val;
        return *this;
    }

    Logger& operator<<(Logger& (*func)(Logger&)) {
        return func(*this);
    }

    void Flush() {
        impl_->Flush();
    }
};










