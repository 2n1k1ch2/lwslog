#include "sinks/FileSink.hpp"

namespace lwslog {
FileSink::FileSink(std::filesystem::path path) : path_(std::move(path)),
    formatter_(&Formatter::defaultFormatter) {
    
    }

FileSink::FileSink(FileSink&& other) noexcept
    : path_(std::move(other.path_)),
      formatter_(std::move(other.formatter_)) {

}


void FileSink::Write(const Messages& msgs)  {
    std::lock_guard<std::mutex> lock(mtx_);
    
    std::ofstream file(path_, std::ios::app);
    if (file.is_open()) {
        for (const auto& msg : msgs) {
            file << formatter_(msg) << std::endl;  
        }
        file.flush();
    }

}

}
