#include <iostream>
#include <string>
#include <cstring>
//#include <csignal>
#include <filesystem>
#ifdef _WIN32
#include "consolecp.h"
#endif
#include "threadsafe_queue.h"
#include "logreader.h"
#include "logparser.h"
#include "database.h"
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

    std::shared_ptr<Database> data = std::make_shared<Database>();  
    std::unique_ptr<IBaseParser> pars = std::make_unique<ParseLogSrv>(data);
    //data.reset();
    pars->parse("*** [30/11/2021 15:36:21] опрос точки 33560 ( УКПГ-10 (ОРЭМ-2 оч.)) запущен ,порт TCP\n"
    "*** точка опроса 190118 - след.опрос в \"29/11/2021 16:30:10\"\n"
    "*** [29/11/2021 16:02:43] опрос точки 335601 ( УКПГ-10 (ОРЭМ-2 оч.)) завершился с кодом 1\n"
	"	опрос 11 завершился с ошибками, всего неудач 3\n");
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;

    auto askue = std::make_shared<threadsafe_queue<std::string>>();
    
    Logreader logreader;
    logreader.intit();

    if(std::filesystem::exists(logreader.getPatch()))
    {
        
        std::string test;
        for(auto run = logreader.start(askue, 500); run ; run = logreader.status())
        {
           
           askue->wait_and_pop(test);
           pars->parse(test);
           
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