#include "sinks/SocketSink.hpp"

namespace lwslog{

    SocketSink::SocketSink(Protocol prtcl, std::string host,int port , asio::io_context* external,
        std::function<std::string(const Message&)> formatter = Formatter::defaultFormatter  ,
        SyncMode mode = SyncMode::SYNC) 
        :formatter_(formatter),
        mode_(mode)
    {
        if (external) {
            ctx_ = external;        // use external, doesnt delete
        } else {
            own_ctx_ = std::make_unique<asio::io_context>();
            ctx_ = own_ctx_.get();
            
        }
        if (prtcl==Protocol::TCP){
            this->socket_impl_=std::make_unique<ISocketImplTCP>(host, port,*ctx_);
        } 
        else {
            this->socket_impl_=std::make_unique<ISocketImplUDP>(host, port,*ctx_);
        }

    }
    SocketSink::~SocketSink() {
        if (own_ctx_) {
            own_ctx_->stop();
            if (ctx_thread_.joinable()) ctx_thread_.join();
        }
    }

    SocketSink::ISocketImplTCP::ISocketImplTCP(const std::string& host,int port,asio::io_context& ctx) : socket_(ctx){
        asio::ip::tcp::resolver resolver(ctx);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        asio::connect(socket_, endpoints);

    }
    SocketSink::ISocketImplUDP::ISocketImplUDP(const std::string& host,int port,asio::io_context& ctx) 
    : socket_(ctx,asio::ip::udp::v4()), endpoint_(asio::ip::make_address(host), port) { }
    void SocketSink::Write(const Messages& msgs) {
        std::lock_guard lock(mtx_);
        this->socket_impl_->Write(msgs,this->formatter_);
    }
    void SocketSink::ISocketImplTCP::Write(const Messages& msgs,std::function<std::string(const Message&)>& formatter ){
        for (auto& m : msgs) {
            std::string data = formatter(m);
            asio::write(socket_, asio::buffer(data));
        }
    }

    void SocketSink::ISocketImplUDP::Write(const Messages& msgs,std::function<std::string(const Message&)>& formatter ){
        for (auto& m : msgs) {
            std::string data = formatter(m);
            socket_.send_to(asio::buffer(data), endpoint_);
        }
    }
}