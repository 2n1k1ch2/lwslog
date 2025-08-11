#pragma once
#include "core/sink.hpp"
#include <functional>
namespace lwslog {
class OstreamSink : public ILogSink {
private:
    std::ostream& stream_;
    std::function<std::string(const Message&)> formatter_;
public:
    explicit OstreamSink(std::ostream& stream,
                         std::function<std::string(const Message&)> formatter = defaultFormatter)
        : stream_(stream), formatter_(std::move(formatter)) {}

    void Write(const Message&& msg) override {
        stream_ << formatter_(msg) << std::endl;
    }

private:
    static std::string defaultFormatter(const Message& msg) {
        return std::format("{:%Y-%m-%d %H:%M:%S} [{}] {}", 
                           msg.timestamp_, 
                           toString(msg.level_), 
                           msg.text_);
    }
};
}