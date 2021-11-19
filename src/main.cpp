#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "getdate.h"



int main()
{
    
    std::filesystem::path path{"auto_211116.log"};
    std::ifstream file;
    

    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    
    std::cout << "Start..." << '\n';

        std::cout << Getdate::GetObject()->getdate_time(lst) << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    
    
    
    std::streampos g = 0;
    while(true)
    {
           file.open(path, std::ios::binary | std::ios::ate);

           if(!file.is_open())
            {
                std::cout << "Error open file \n";
            }
            else
            {
                auto gnew = file.tellg();   
                if(g < gnew)
                {
                    auto temp = gnew;
                    gnew-= g;
                    std::string str(gnew, '\0');
                    file.seekg(g);
                    file.read(&str[0], gnew);
                    std::cout << str;
                    g = temp;
                }
                else
                {
                    g = gnew;
                }

            }

            file.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } 
   Getdate::Destroy();
}