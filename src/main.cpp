#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <clocale>
#include "getdate.h"
#include "logreader.h"


int main()
{
    setlocale(LC_CTYPE,"Russian");//Так же требуется кодировка исходника Windows 1251 + в скосоле cmd шрифт Lucida console
    
    std::filesystem::path path{"auto_211122.log"};
    std::ifstream file;
    

    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    
    std::cout << "Привет..." << '\n';

        std::cout << Getdate::GetObjectDate()->getdate_time(lst) << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   
     Logreader logreader(path.string());
    if(Logerstatus::LOG_FILE_OPEN_ERROR == logreader.start())
    {
        std::cout << "Error\n";
    }

   Getdate::Destroy();
}