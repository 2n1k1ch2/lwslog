#include "sinks/FileSink.hpp"

namespace lwslog {
    FileSink::FileSink(std::filesystem::path path) : path_(path){}
    void FileSink::Write(const Message& msg) {
        std::lock_guard<std::mutex> lock();
        out_.open(path_);
        if(out_.is_open()){
            out_<<formatter_(msg)<<std::endl;
        }
        out_.close();
    }
}