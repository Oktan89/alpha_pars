#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <clocale>
#include "getdate.h"
#include "logreader.h"


int main()
{
    setlocale(LC_CTYPE,"Russian");//��� �� ��������� ��������� ��������� Windows 1251 + � ������� cmd ����� Lucida console
    
    std::filesystem::path path{"auto_211122.log"};
    std::ifstream file;
    

    const auto lst = {'y', 'm', 'd', ' ', 'H', ':', 'M', ':', 'S'};
    
    std::cout << "Тест..." << '\n';

        std::cout << Getdate::GetObjectDate()->getdate_time(lst) << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   
     Logreader logreader(path.string());
    if(Logerstatus::LOG_FILE_OPEN_ERROR == logreader.start())
    {
        std::cout << "Error\n";
    }

   //Getdate::Destroy();
}