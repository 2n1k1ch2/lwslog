#pragma once
#include "OstreamSink.hpp"
#include "utils/formatter.hpp"
#include "core/sink.hpp"
#include <fstream>
#include <mutex>
#include <filesystem>
namespace lwslog {
class FileSink : public ILogSink {
private:
    
    std::filesystem::path path_;
    mutable std::mutex mtx_;
    std::function<std::string(const Message&)> formatter_;
public:
    void Write(const Messages& msgs)  override  ;
    explicit FileSink(std::filesystem::path path);
    FileSink(FileSink&& other) noexcept;
    
    virtual ~FileSink() = default;
    FileSink& operator=(const FileSink&) = delete;
    FileSink& operator=(FileSink&&) = delete;
};
}
