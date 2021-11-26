#include <iostream>
#include <thread>
#include "logreader.h"
#include "getdate.h"

#define DEBUG


Logreader::Logreader(const std::filesystem::path &path) noexcept : _path(path)
{
    //Открываем файл на чтение с позицией курсора на конец файла
    _file.open(_path, std::ios::binary | std::ios::ate);

    if (_file.is_open())
    {
        //Если файл открыт, сохраняем позицию курсора конца файла
        _savepos = _file.tellg();
        _file.close();
        _status = Logerstatus::LOG_FILE_CLOSE;
    }
    else
    {
        _status = Logerstatus::LOG_FILE_OPEN_ERROR;
    }
}

Logerstatus Logreader::start(const int64_t timer_ms)
{
    run = true;

    auto t = std::thread(&Logreader::thred_log_read, this, timer_ms);
    _log_thread.swap(t); ///??????
    return _status;
}

void Logreader::thred_log_read(int64_t timer_ms)
{
    while (run)
    {
        _file.open(_path, std::ios::binary | std::ios::ate);

            if (_file.is_open())
            {
                _status = Logerstatus::LOG_FILE_OPEN;
                //читаем тикущюю позицию курсора в конце файла
                auto gnew = _file.tellg();
                //если сохраненая позиция меньше то нужно прочитать новую запись в отслеживаемом файле
                if (_savepos < gnew)
                {
                    auto temp = gnew;
                    gnew -= _savepos;
                    std::string str(gnew, '\0');
                    _file.seekg(_savepos);
                    _file.read(&str[0], gnew);
                    std::cout << str;
                    #ifdef DEBUG
                        std::cout << "[--------------------------]\n";
                    #endif
                    _savepos = temp;
                }
                else
                {
                    _savepos = gnew; //Для случая если файл был усечен
                }
                _file.close();
                _status = Logerstatus::LOG_FILE_CLOSE;
            }
            else
            {
                _status = Logerstatus::LOG_FILE_OPEN_ERROR;
            }
        std::this_thread::sleep_for(std::chrono::milliseconds(timer_ms));
    }

}

void Logreader::stop()
{
    run = false;
    if(_log_thread.joinable())
    {
        _log_thread.join();
        std::cout << "thread stop\n";
    }
}

Logreader::~Logreader()
{
    stop();
}

void Logreader::setNewfileDependingCurdate(const std::filesystem::path &oldpatch)
{
    std::filesystem::path path{"/Alphacenter/logsrv/auto_"+Getdate::GetObjectDate()->getdate_time({'y', 'm', 'd'})+".log"};
}