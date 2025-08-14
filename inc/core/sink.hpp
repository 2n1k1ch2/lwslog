#pragma once
#include "core/message.hpp"
namespace lwslog{
class ILogSink {
public:
    virtual ~ILogSink() = default;
    virtual void Write(const Messages& msgs) = 0;
};
}