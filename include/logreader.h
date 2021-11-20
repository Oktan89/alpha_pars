#pragma once
#include <fstream>

enum class Logerstatus
{
    FILE_OPEN,
    FILE_CLOSE,
    FILE_OPEN_ERROR
};

class Logreader
{
    std::streampos _savepos = 0;
    std::ifstream _file;
    const std::string _path;
    Logerstatus _status{Logerstatus::FILE_CLOSE};
    bool run{true};

public:

    Logreader(const std::string& path) noexcept; 

    Logreader(const Logreader& other) = delete;

    Logerstatus start();

};