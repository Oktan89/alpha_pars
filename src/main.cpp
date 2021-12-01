#include <iostream>
#include <string>
//#include <csignal>
#include <filesystem>
#ifdef _WIN32
#include "consolecp.h"
#endif
#include "threadsafe_queue.h"
#include "logreader.h"
#include "logparser.h"
#include "pcout.h" // thread safe cout

/*std::atomic_bool interrupted{};
extern "C" void handler(int signal)
{
    std::cout << "Handler invoked with signal " << signal << ".\n";
    interrupted = true;
}*/

int main()
{
    //std::signal(SIGINT, handler);

    #ifdef _WIN32
        ConsoleCP console(1251);
    #elif __linux__
        
    #endif
    
    std::unique_ptr<IBaseParser> pars = std::make_unique<ParseLogSrv>();
    
    pars->parse("*** [29/11/2021 15:36:11] опрос точки 330357 (АУП (блок Б) Железнодорожная 8 от ТП-5А) запущен ,порт COM31\n *** точка опроса 190118 - след.опрос в \"29/11/2021 16:30:10\"\n");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;

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