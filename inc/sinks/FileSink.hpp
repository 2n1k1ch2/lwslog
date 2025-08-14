#include "OstreamSink.hpp"
#include "core/sink.hpp"
#include <fstream>
#include <mutex>
#include <filesystem>
namespace lwslog {
class FileSink : public ILogSink {
private:
    std::fstream out_;
    std::filesystem::path path_;
    std::mutex mtx;
    std::function<std::string(const Message&)> formatter_;
public:
    void Write(const Message& msg) override;
    explicit FileSink(std::filesystem::path path);
};
}
