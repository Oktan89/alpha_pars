#pragma once
#include <iostream>
#include <mutex>
#include <string>
#include <ctime>

///Singleton
class Getdate
{
    static Getdate *_date;
    static std::mutex _m_date;
    std::time_t time_now;
    std::tm* _tm{};

protected:
    void update();
    
    Getdate() : time_now(std::time(nullptr)), _tm(std::localtime(&time_now)){}
    
    ~Getdate(){}

public:
    
    Getdate(const Getdate& other) = delete;
    
    Getdate &operator=(const Getdate&) = delete;

    static Getdate *GetObjectDate();

    static void Destroy();

    std::string getdate_time(std::initializer_list<char> lst);

};

