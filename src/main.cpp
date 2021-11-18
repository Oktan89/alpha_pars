#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>
#include "getdate.h"


int main()
{
    //std::string path{"auto_211116.log"};
    std::filesystem::path path{"auto_211116.log"};
    std::ifstream file;
    Getdate d;
    //const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    

  /*  while(true)
    {
        std::cout << d.getdate(lst) << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }*/
   while(true)
    {
            file.open(path, std::ios::ate);
           if(!file.is_open())
            {
                std::cout << "Error open file \n";
            }
            else
            {
                std::cout << file.tellg() << "\n";   
                std::cout << "File size: " << std::filesystem::file_size(path) << "\n";//Определяем размер файла средствами операционной системы
            }
            file.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
 

}