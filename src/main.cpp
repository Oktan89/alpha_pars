#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <filesystem>
#ifdef _WIN32
#include <clocale>
#endif
#include "getdate.h"
#include "logreader.h"


int main()
{
    
    
    #ifdef _WIN32
        setlocale(LC_CTYPE,"Russian");//Windows 1251 + cmd Lucida console
        //std::filesystem::path path{"/Alphacenter/logsrv/auto_"+Getdate::GetObjectDate()->getdate_time({'y', 'm', 'd'})+".log"};
        std::filesystem::path path{"auto_211116.log"};
    #elif __linux__
        std::filesystem::path path{"auto_211116.log"};
    #endif

    //Запуск потока в опредлееное время!!!!!
   /* std::tm tm{};
    tm.tm_hour = 1;
    tm.tm_min = 39;
    tm.tm_sec = 0;
    tm.tm_mon = 11-1;
    tm.tm_mday = 29;
    tm.tm_year = 2021 - 1900;
    
    //tm.tm_isdst = -1; // Use DST value from local time zone
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    std::this_thread::sleep_until(tp);
    std::cout<<"!!!!"<<std::endl;*/
    Logreader logreader(path);

    if(std::filesystem::exists(path))
    {
        
        logreader.start(500);
        //logreader.stop();
    }
    else
    {
        std::cout << "Not dir\n";
    }
    int get;
    std::cin>>get;
    //std::cout<< Getdate::GetObjectDate()->getdate_time({'y', 'm', 'd', ' ', 'H','M','S'});
    //Getdate::Destroy();
    return 0;
}

      /* for(auto &file : std::filesystem::directory_iterator(path))
            std::cout << file.path().filename().string() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));*/