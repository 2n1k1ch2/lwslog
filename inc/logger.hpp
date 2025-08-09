#pragma once 

#include "message.hpp"
#include "sink.hpp"

#include <memory>
#include <string>
#include <vector>
#include <memory>

namespace Logger{
enum class LogLevel {
    TRACE,   // Detail debug information
    DEBUG,   // Debug messages
    INFO,    // information messages
    WARN,    // warnings
    ERROR,   // errors
    FATAL    // fatal errors
};

class Logger {
private:
    mutable  std::vector<std::shared_ptr<ILogSink>> sinks_;
    LogLevel curr_level_;
    mutable  std::ostringstream oss_;
public:
    Logger(){}; 
    const Logger(LogLevel level)  : curr_level_(level)  {}
    friend Logger& Flush(Logger& logger);
    template<typename T>
    Logger& operator<<(const T& val) const{
        oss_<<curr_level_<<val;
    }

    Logger& operator<<(Logger& (*func)(Logger&)) {
        return func(*this);
    }
    Logger& operator<<(LogLevel level)  {
        curr_level_=level;
        return *this;
    }
    

    
};
Logger& Flush(Logger& logger) {
    Message msg(logger.oss_.str());
    for(const auto sink : logger.sinks_){
        sink->Write(msg);
    }
}

auto endl = Flush;

}
