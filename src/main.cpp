#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <filesystem>
#ifdef _WIN32
#include <clocale>
#endif
#include "threadsafe_queue.h"
#include "logreader.h"
#include "logparser.h"
#include "pcout.h" // ???????????????? cout


int main()
{
    #ifdef _WIN32
        setlocale(LC_ALL,"");//Windows 1251 + cmd Lucida console
    #elif __linux__
        std::filesystem::path path{"auto_211116.log"};
    #endif
    
   /* IBaseParser *pars = new ParseLogSrv;
    pars->parse("*** ???? ????? ?????");
    delete pars;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;*/

    threadsafe_queue<std::string> askue;
    
    Logreader logreader;
    logreader.intit();

    if(std::filesystem::exists(logreader.getPatch()))
    {
        
        logreader.start(askue, 500);
        std::string test;
        while(true)
        {
            askue.wait_and_pop(test);
            pcout{} << test;
        }
        
        
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