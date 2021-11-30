#pragma once
#include <string>
#include <map>

struct ObjectAskue
{
    
};


class IBaseParser
{
public:
    virtual void parse(const std::string& log) = 0;
    virtual ~IBaseParser(){}
};

class ParseLogSrv : public IBaseParser
{
public:
    void parse(const std::string& log) override
    {
       std::size_t pos = log.find("***");
       std::cout << pos << log <<"\n";
    }
    ~ParseLogSrv(){}
    
};