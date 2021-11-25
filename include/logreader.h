#pragma once
#include <filesystem>
#include <fstream>

enum class Logerstatus
{
    LOG_FILE_OPEN,
    LOG_FILE_CLOSE,
    LOG_FILE_OPEN_ERROR
};

class Logreader
{
    std::streampos _savepos = 0;
    std::ifstream _file;
    std::filesystem::path _path;
    Logerstatus _status{Logerstatus::LOG_FILE_CLOSE};
    bool run{true};
    void thred_log_read();

public:
    
    Logreader(const std::filesystem::path &path) noexcept; 

    Logreader(const Logreader &other) = delete;

    Logerstatus start(int64_t timer_ms = 1000);

};