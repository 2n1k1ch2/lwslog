#pragma once
#include "core/message.hpp"
#include <string>
namespace lwslog {
class Formatter {
public: 
    static std::string defaultFormatter(const Message& msg) {
    return std::format("{:%Y-%m-%d %H:%M:%S} [{}] {}", 
                        msg.timestamp_, 
                        toString(msg.level_), 
                        msg.text_);
    }
};
}