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
    "*** [29/11/2021 15:35:33] ��������������� ���� ������ ��-�� ���������� ����.�������"

"*** [29/11/2021 15:35:37] ����� ����� 260801 (�� \"������-����\") ������� ,���� TCP"

"*** [29/11/2021 15:35:45] ����� ����� 19001194( moxa port4) ���������� � ����� 1"
		"����� 1112109 ���������� �������, ����� ������ 0"
		"����� 1111713 ���������� �������, ����� ������ 0"
		"����� 1112120 ���������� � ��������, ����� ������ 1"
		"����� 1111883 ���������� �������, ����� ������ 0"
		"����� 1112051 ���������� �������, ����� ������ 0"
		"����� 1238874 ���������� � ��������, ����� ������ 33"
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