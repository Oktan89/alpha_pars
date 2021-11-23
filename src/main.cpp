#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <clocale>
#include "getdate.h"
#include "logreader.h"


int main()
{
    setlocale(LC_CTYPE,"Russian");//пїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ Windows 1251 + пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ cmd пїЅпїЅпїЅпїЅпїЅ Lucida console
    
    std::filesystem::path path{"/Alphacenter/logsrv/auto_"+Getdate::GetObjectDate()->getdate_time({'y', 'm', 'd'})+".log"};
    if(std::filesystem::exists(path))
    {
        Logreader logreader(path.string());
        if(Logerstatus::LOG_FILE_OPEN_ERROR == logreader.start())
        {
            std::cout << "Error\n";
        }
      /* for(auto &file : std::filesystem::directory_iterator(path))
            std::cout << file.path().filename().string() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));*/
    }
    Getdate::Destroy();
    std::cout << "Not dir" << std::endl;
    return 0;
    /*std::filesystem::path path{"auto_211123.log"};
    std::ifstream file;
    

    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    
    std::cout << "Тест..." << '\n';

        std::cout << Getdate::GetObjectDate()->getdate_time(lst) << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   
     Logreader logreader(path.string());
    if(Logerstatus::LOG_FILE_OPEN_ERROR == logreader.start())
    {
        std::cout << "Error\n";
    }*/

   //Getdate::Destroy();
}