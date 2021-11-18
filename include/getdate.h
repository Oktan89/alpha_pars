#pragma once
#include <iostream>
#include <string>
#include <ctime>

class Getdate final
{
    std::time_t time_now;
    std::tm* _tm{};

    void update()
    {
        time_now = std::time(nullptr);
        _tm = std::localtime(&time_now);
    }

public:
    Getdate() : time_now(std::time(nullptr)), _tm(std::localtime(&time_now)){}
    
    std::string getdate(std::initializer_list<char> lst);


    int get_year() const
    {
        return _tm->tm_year%100;
    }

    const std::tm *get_tm_struct() const
    {
        return _tm;
    }
};