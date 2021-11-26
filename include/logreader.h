#pragma once
#include <filesystem>
#include <thread>
#include <atomic>
#include <fstream>

enum class Logerstatus
{
    LOG_FILE_OPEN,
    LOG_FILE_CLOSE,
    LOG_FILE_OPEN_ERROR
};

class Logreader
{
private:
    std::streampos _savepos = 0;
    std::ifstream _file;
    std::filesystem::path _path;
    Logerstatus _status{Logerstatus::LOG_FILE_CLOSE};
    std::thread _log_thread;
    std::atomic<bool> run = false;
    void thred_log_read(int64_t timer_ms);

public:
    
    Logreader(const std::filesystem::path &path) noexcept; 

    Logreader(const Logreader &other) = delete;

    Logreader& operator=(const Logerstatus& other) = delete;

    Logerstatus start(int64_t timer_ms = 1000);

    void stop();

    ~Logreader();

};