#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>

#if defined __windows__
#include <clocale>
#endif

#include "getdate.h"


int main()
{
    #if defined (__windows__)
    setlocale(LC_CTYPE, "");
    #elif defined (__linux__)
    setlocale(LC_CTYPE, "Russian_Russia.1251");
    #endif
    
    std::filesystem::path path{"auto_211116.log"};
    std::ifstream file;
    Getdate d;
    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    

    std::cout << "Старт..." << '\n';
    std::cout << d.getdate(lst) << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    
   /* while(true)
    {
            file.open(path, std::ios::ate);
           if(!file.is_open())
            {
                std::cout << "Error open file \n";
            }
            else
            {
                std::cout << file.tellg() << "\n";   
                std::cout << "File size: " << std::filesystem::file_size(path) << "\n";//Определяем размер файла средствами операционной системы
            }
            file.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } */

}