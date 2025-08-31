#pragma once
#include <mutex>
#include <functional>
#include "utils/formatter.hpp"
#include "core/sink.hpp"
#include <asio.hpp>
#include <memory>
namespace lwslog {
enum class Protocol { TCP, UDP };
class SocketSink : public ILogSink {
private:
class ISocketImpl{
public:
    virtual ~ISocketImpl() = default;
    virtual void Write(const Messages& msgs,std::function<std::string(const Message&)>&) = 0;
};
class ISocketImplTCP:public ISocketImpl{
private:
    asio::ip::tcp::socket socket_;
public:
    ISocketImplTCP(const std::string& host, int port,asio::io_context& ctx);
    void Write(const Messages& msgs,std::function<std::string(const Message&)>& formatter ) override;
};
class ISocketImplUDP: public ISocketImpl{
private:
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint endpoint_;
public:
    ISocketImplUDP(const std::string& host ,int port,asio::io_context& ctx);
    void Write(const Messages& msgs,std::function<std::string(const Message&)>& formatter) override;
};


std::function<std::string(const Message&)> formatter_;
mutable std::mutex mtx_;
asio::io_context* ctx_;                        // doesn't own
std::unique_ptr<asio::io_context> own_ctx_;    // own
std::thread ctx_thread_;
std::unique_ptr<ISocketImpl> socket_impl_;
public: 
    virtual ~SocketSink() = default;
    SocketSink(Protocol prtcl , std::string host, int port,asio::io_context* external = nullptr);
    void Write(const Messages& msgs) ;

};

}