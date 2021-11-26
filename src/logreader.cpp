#include <iostream>
#include <thread>
#include <cassert>
#include "logreader.h"
#include "getdate.h"

#define DEBUG


Logreader::Logreader(const std::filesystem::path &path) noexcept : _path(path)
{
    //Открываем файл на чтение с позицией курсора на конец файла
    _file.open(_path, std::ios::binary | std::ios::ate);

    if (_file.is_open())
    {
        #ifdef DEBUG
            std::cout << "[Logreader "<<this<<"]: Check file open... OK\n";
        #endif
        //Если файл открыт, сохраняем позицию курсора конца файла
        _savepos = _file.tellg();
        _file.close();
        _status = Logerstatus::LOG_FILE_OK;
    }
    else
    {
        #ifdef DEBUG
            std::cout << "[Logreader "<<this<<"]: Check file open... ERROR\n";
        #endif
        _status = Logerstatus::LOG_FILE_ERROR;
    }
}

void Logreader::start(const int64_t timer_ms)
{
    run = true;
    assert(!_log_thread.joinable());
    
    auto t = std::thread(&Logreader::thred_log_read, this, timer_ms);
    _log_thread.swap(t);
    _status = Logerstatus::LOG_FILE_RUN;
    #ifdef DEBUG
        std::cout << "[Thread Logreader "<<_log_thread.get_id()<<"]: start\n";
    #endif
}

void Logreader::thred_log_read(int64_t timer_ms)
{
    while (run)
    {
        setNewfileDependingCurdate(_path);
        _file.open(_path, std::ios::binary | std::ios::ate);

            if (_file.is_open())
            {
                _status = Logerstatus::LOG_FILE_OK;
                //читаем новую позицию курсора в конце файла
                auto gnew = _file.tellg();
                //если сохраненая позиция меньше то нужно прочитать новую запись в отслеживаемом файле
                if (_savepos < gnew)
                {
                    auto temp = gnew; //сохраняем во временную переменную позицию конца файла
                    gnew -= _savepos; //вычисляем колличество символов с последнего окрытия файла
                    std::string strbuff(static_cast<std::size_t>(gnew), '\0'); //создаем буфер для чтения вычесленного коллиества символов
                    _file.seekg(_savepos);//переводим курсор на ранее сохраненное место конца файла
                    _file.read(&strbuff[0], gnew);//и читаем с этого места колличество вычисленных символов
                    std::cout << strbuff;//что то делаем с информацией!!!!!
                    #ifdef DEBUG
                        std::cout << "[Thread Logreader "<<_log_thread.get_id()<<"]:<-------------------------->\n";
                    #endif
                    _savepos = temp; //сохраняем новую позицию конца файла
                }
                else
                {
                    _savepos = gnew; //Для случая если файл был усечен, сохраняем новою позицию конца файла
                }
                _file.close();
            }
            else
            {
                _status = Logerstatus::LOG_FILE_ERROR;
            }
        std::this_thread::sleep_for(std::chrono::milliseconds(timer_ms));
    }

}

void Logreader::stop()
{
    run = false;
    if(_log_thread.joinable())
    {
        #ifdef DEBUG
            std::cout << "[Thread Logreader "<<_log_thread.get_id()<<"]: stop\n";
        #endif
        _log_thread.join();
    }
    _status = Logerstatus::LOG_FILE_STOP;
}

Logreader::~Logreader()
{
    stop();
    #ifdef DEBUG
            std::cout << "[Logreader "<<this<<"]: ~Delete... OK\n";
    #endif
}

//Если сменилась дата то меняем название файла
void Logreader::setNewfileDependingCurdate(const std::filesystem::path &oldpatch)
{
    AlphacentrPatch patch_name;
    std::string file_name = Getdate::GetObjectDate()->getdate_time({'y', 'm', 'd'});
    std::filesystem::path newpath{patch_name.logsrv + file_name + patch_name.extension};
    if(oldpatch != newpath)
    {
        _path.swap(newpath);
        #ifdef DEBUG
            std::cout << "[Thread Logreader "<<_log_thread.get_id()<<"]: set new file name "<< _path<<"\n";
        #endif
    }
        
  
}

Logerstatus Logreader::status() const noexcept
{
    return _status;
}