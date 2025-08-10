#pragma once
#include "logger.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <chrono>

namespace Logger {
using Messages = std::vector<Message>;

class Message {
private:
    std::chrono::system_clock::time_point timestamp_;
    LogLevel level_;
    std::string text_;

public:
    template<typename T>
    Message(LogLevel level, std::string && text) : 
    level_(level) ,
    text_(std::move(text)),
    timestamp_(std::chrono::system_clock::now()) {}
};
}