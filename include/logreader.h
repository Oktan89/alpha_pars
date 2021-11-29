#pragma once
#include <filesystem>
#include <thread>
#include <mutex>
#include <atomic>
#include <fstream>
#include "pcout.h"
#include "getdate.h"


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
    std::streampos _savepos;
    std::ifstream _file;
    std::filesystem::path _path;
    std::atomic<Logerstatus> _status;
    std::thread _log_thread;
    std::atomic<bool> run;
    std::mutex _m_locfilepatch;
    Getdate *_getdate;

    void thred_log_read(const int64_t timer_ms);

    void setNewfileDependingCurdate(const std::filesystem::path &oldpatch);
    void autoSetNewfileDependingCurdate();

public:
    
    Logreader(const std::filesystem::path &path  = "auto_211116.log") noexcept; 

    Logreader(const Logreader &other) = delete;

    Logreader& operator=(const Logerstatus& other) = delete;

    void intit();

    void start(int32_t timer_ms = 1000);

    void stop();

    Logerstatus status() const noexcept;

    std::filesystem::path getPatch() const noexcept;

    ~Logreader();

};