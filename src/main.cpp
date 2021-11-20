#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "getdate.h"
#include "logreader.h"



int main()
{
    
    std::filesystem::path path{"auto_211116.log"};
    std::ifstream file;
    

    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    
    std::cout << "Start..." << '\n';

        std::cout << Getdate::GetObject()->getdate_time(lst) << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    Logreader logreader(path);
    if(Logerstatus::FILE_OPEN_ERROR == logreader.start())
    {
        std::cout << "Error\n";
    }

   Getdate::Destroy();
}