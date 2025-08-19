#include "SocketSink.hpp"
namespace lwslog {
    SocketSink::SocketSink(asio::io_context& io, const std::string& host, int port ,
                           std::function<std::string(const Message&)> formatter = Formatter::defaultFormatter ) : socket_(io) ,
                            formatter_(std::move(formatter)) {
        asio::ip::tcp::resolver resolver(io);
        asio::connect(socket_, resolver.resolve(host, std::to_string(port)));
    }

    void SocketSink::Write(const Messages& msgs)  {
        std::lock_guard<std::mutex> lock();
        for(const auto & msg : msgs){
            asio::write(socket_, asio::buffer(formatter_(msg)));
        }
    }
}