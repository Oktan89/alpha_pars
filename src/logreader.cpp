#include <iostream>
#include <thread>
#include "logreader.h"


Logreader::Logreader(const std::string &path) noexcept : _path(path)
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

Logerstatus Logreader::start(int64_t time_ms)
{
    //Если файл неоткрывается или статус работы выключен то завершаем чтение
    while ((_status != Logerstatus::LOG_FILE_OPEN_ERROR) && run)
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
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
    }
    return _status;
}