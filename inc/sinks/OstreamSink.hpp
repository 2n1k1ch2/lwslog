#pragma once
#include "core/sink.hpp"
#include <functional>
#include "utils/formatter.hpp"
namespace lwslog {
class OstreamSink : public ILogSink {
private:
    std::ostream& stream_;
    std::function<std::string(const Message&)> formatter_;
public:
    explicit OstreamSink(std::ostream& stream,
                         std::function<std::string(const Message&)> formatter = Formatter::defaultFormatter)
        : stream_(stream), formatter_(std::move(formatter)) {}

    void Write(const Messages& msgs) override {
        for (const auto & msg : msgs) {
            stream_ << formatter_(msg) << std::endl;
        }
    }

};
}