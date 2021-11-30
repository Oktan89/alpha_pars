#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <filesystem>
#ifdef _WIN32
#include <clocale>
#endif
#include "logreader.h"
#include "pcout.h" // потокобезопасный cout


int main()
{
    
    
    #ifdef _WIN32
        setlocale(LC_CTYPE,"Russian");//Windows 1251 + cmd Lucida console
    #elif __linux__
        std::filesystem::path path{"auto_211116.log"};
    #endif

  
    Logreader logreader;
    logreader.intit();

    if(std::filesystem::exists(logreader.getPatch()))
    {
        
        logreader.start(500);
        
    }
    else
    {
        pcout{} << "Not dir\n";
    }
    int get;
    std::cin>>get;
    
    return 0;
}

      /* for(auto &file : std::filesystem::directory_iterator(path))
            std::cout << file.path().filename().string() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));*/