#pragma once

#include "message.hpp"
#include "sink.hpp"

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>
#include <concepts>

namespace Logger {

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger {
private:
    mutable std::vector<std::shared_ptr<ILogSink>> sinks_;
    LogLevel curr_level_;
    std::ostringstream oss_;
    mutable Messages msgs_;

public:
    Logger() = default;
    explicit Logger(LogLevel level) : curr_level_(level) {}

    friend Logger& Flush(Logger& logger);

    template<typename T>
    Logger& operator<<(const T& val) const {
        oss_ << val;
        return *this;
    }

    Logger& operator<<(Logger& (*func)(Logger&)) {
        return func(*this);
    }

    Logger& operator<<(LogLevel level) {
        curr_level_ = level;
        return *this;
    }

    template<typename... Ts>
    requires ((std::derived_from<std::remove_reference_t<Ts>, ILogSink>) && ...)
    void Add_Sink(Ts&&... sinks) {
        (sinks_.push_back(std::make_shared<std::remove_reference_t<Ts>>(std::forward<Ts>(sinks))), ...);
    }
};

inline Logger& Flush(Logger& logger) {
    logger.msgs_.emplace_back(Message(logger.curr_level_, logger.oss_.str()));
    logger.oss_.str("");   // reset accumulated text
    logger.oss_.clear();   // reset flags
    return logger;
}

inline auto endl = Flush;

} // namespace Logger
