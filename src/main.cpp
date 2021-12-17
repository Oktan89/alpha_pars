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
//#include "boost/asio"


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
   /* pars->parse(
    "*** [29/11/2021 15:35:33] диагностический файл усечен из-за превышения макс.размера"

"*** [29/11/2021 15:35:37] опрос точки 260801 (КС \"Ямбург-Елец\") запущен ,порт TCP"

"*** [29/11/2021 15:35:45] опрос точки 19001194( moxa port4) завершился с кодом 1"
		"опрос 1112109 завершился успешно, всего неудач 0"
		"опрос 1111713 завершился успешно, всего неудач 0"
		"опрос 1112120 завершился с ошибками, всего неудач 1"
		"опрос 1111883 завершился успешно, всего неудач 0"
		"опрос 1112051 завершился успешно, всего неудач 0"
		"опрос 1238874 завершился с ошибками, всего неудач 33"
    );
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return 0;*/

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