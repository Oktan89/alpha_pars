#include <iostream>
#include <string>
//#include <thread>
#include <filesystem>
#ifdef _WIN32
#include <clocale>
#endif
#include "threadsafe_queue.h"
#include "logreader.h"
#include "logparser.h"
#include "pcout.h" // thread safe cout


int main()
{
    #ifdef _WIN32
        setlocale(LC_ALL,"");//Windows 1251 + cmd Lucida console
    #elif __linux__
        std::filesystem::path path{"auto_211116.log"};
    #endif
    
    /*std::unique_ptr<IBaseParser> pars = std::make_unique<ParseLogSrv>();
    
    pars->parse("*** [01/02/2021 00:00:01]");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;*/

    auto askue = std::make_shared<threadsafe_queue<std::string>>();
    
    Logreader logreader;
    logreader.intit(false);

    if(std::filesystem::exists(logreader.getPatch()))
    {
        
        //logreader.start(askue, 500);
        std::string test;
        for(auto run = logreader.start(askue, 500); run ; run = logreader.status())
        {
            askue->wait_and_pop(test);
            pcout{} << test;
            //logreader.stop();          
        }
        
    }
    else
    {
        pcout{} << "Log file not found\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
        
    return 0;
}

      /* for(auto &file : std::filesystem::directory_iterator(path))
            std::cout << file.path().filename().string() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));*/