#include <message.hpp>
namespace Logger{
class ILogSink {

    public:
    virtual ~ILogSink() = default;
    virtual void Write(Message msg) = 0;
};
}