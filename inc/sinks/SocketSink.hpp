#define ASIO_STANDALONE
#include "core/sink.hpp"
#include "utils/formatter.hpp"
#include <asio.hpp>
#include <mutex>

namespace lwslog {

class SocketSink : public ILogSink {
private:
    asio::ip::tcp::socket socket_;
    std::function<std::string(const Message&)> formatter_;
public:
    SocketSink(asio::io_context& io, const std::string& host, int port, std::function<std::string(const Message&)> formatter = Formatter::defaultFormatter);

    void Write(const Messages& msg) override;
};
}