#pragma once
#include <filesystem>
#include <thread>
#include <atomic>
#include <fstream>

enum class Logerstatus
{
    LOG_FILE_OK,
    LOG_FILE_RUN,
    LOG_FILE_STOP,
    LOG_FILE_ERROR    
};

struct AlphacentrPatch
{
    const char* logsrv{"/Alphacenter/logsrv/auto_"};
    const char* extension{".log"};
};

class Logreader
{
private:
    std::streampos _savepos = 0;
    std::ifstream _file;
    std::filesystem::path _path;
    std::atomic<Logerstatus> _status{Logerstatus::LOG_FILE_STOP};
    std::thread _log_thread;
    std::atomic<bool> run = false;

    void thred_log_read(const int64_t timer_ms);

    void setNewfileDependingCurdate(const std::filesystem::path &oldpatch);

public:
    
    Logreader(const std::filesystem::path &path) noexcept; 

    Logreader(const Logreader &other) = delete;

    Logreader& operator=(const Logerstatus& other) = delete;

    void start(int64_t timer_ms = 1000);

    void stop();

    Logerstatus status() const noexcept;

    ~Logreader();

};