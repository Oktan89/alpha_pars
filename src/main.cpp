#include <iostream>
#include <string>
#include <thread>
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