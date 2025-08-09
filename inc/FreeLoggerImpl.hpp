#include "logger.hpp"
#include "chrono"
#include "optional"
class FreeLoggerImpl : public ILoggerImpl {
private:
    std::ostream os;
    std::chrono::time_point<std::chrono::system_clock> time_point_;
    std::optional<LogLevel> currentLevel_;
    std::
public:
    template<typename T>
    FreeLoggerImpl& operator<<(const T& val) {
        os<<val;
        return this;
    }
    FreeLoggerImpl& operator<<(FreeLoggerImpl& (*func)(FreeLoggerImpl&) ) {
        func(*this);

        return *this;
    }
    void Flush(){
        
    }
};