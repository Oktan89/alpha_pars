#pragma once
#include <string>
#include <ctime>
#include <map>
#include "pcout.h"

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
    
    std::tm convertFindTime(const std::string& time);

public:

    void parse(const std::string& log) override;

    ~ParseLogSrv(){}
    
};

