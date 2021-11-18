#pragma once
#include <iostream>
#include <ctime>

class Getdata
{
    std::time_t time_now;
    std::tm* _tm{};

public:
    Getdata() : time_now(std::time(nullptr)), _tm(std::localtime(&time_now)){}
    
    void data() const
    {

        std::cout << std::asctime(_tm);
        std::cout << _tm->tm_year%100 << "\n";
    }
};