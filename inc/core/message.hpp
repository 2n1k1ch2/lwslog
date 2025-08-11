#pragma once

#include "core/level.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

namespace lwslog {


struct Message {

    std::chrono::system_clock::time_point timestamp_;
    LogLevel level_;
    std::string text_;


    
    Message(LogLevel level, std::string && text) : 
    level_(level) ,
    text_(std::move(text)),
    timestamp_(std::chrono::system_clock::now()) {}
    
    
};
using Messages = std::vector<Message>;
}