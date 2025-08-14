#pragma once 

#include "core/message.hpp"
#include "core/sink.hpp"
#include "core/level.hpp"
#include <memory>
#include <string>
#include <vector>


namespace lwslog{

template<typename T>
concept SinkDerived = std::is_base_of_v<ILogSink, std::remove_reference_t<T>>;

class Logger {
private:
    mutable  std::vector<std::shared_ptr<ILogSink>> sinks_;
    LogLevel curr_level_;
    mutable std::ostringstream oss_;
    mutable  Messages msgs_;
public:
    Logger(){}; 
    Logger(LogLevel level)  : curr_level_(level)  {}
    friend Logger& Flush(Logger& logger);
    template<typename T>
    Logger& operator<<(const T& val) const{
        oss_<<val; 
        return const_cast<Logger&>(*this);
    }

    Logger& operator<<(Logger& (*func)(Logger&)) {
        return func(*this);
    }
    Logger& operator<<(LogLevel level)  {
        curr_level_=level;
        return *this;
    }

    

    template<SinkDerived... Ts>
    void Add_Sink(Ts&&... sinks) {
        (sinks_.push_back(std::make_shared<std::remove_reference_t<Ts>>(std::forward<Ts>(sinks))), ...);
    }


    
};
Logger& Flush(Logger& logger) {
    logger.msgs_.emplace_back(Message(logger.curr_level_, logger.oss_.str()));
    logger.oss_.str("");   //  resetting the accumulated row
    logger.oss_.clear();   //  resetting the flow flags
    for(auto & sink : logger.sinks_){
        sink->Write(logger.msgs_);
    }
    logger.msgs_.clear();
    return logger;
}

auto endl = Flush;

}
