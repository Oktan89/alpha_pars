#pragma once
#include <string>
#include <map>
#include <utility>
#include <ostream>
#include "pcout.h"
#include "textprotocol.h"

//Тип интерфейса опроса
enum class INTERFACETYPE
{
    COM,
    TCP,
    NONE
};

//Структура времени в логах АЦ
struct Time_stamp
{
    int day;
    int mon;
    int year;
    int hour;
    int min;
    int sec;
    Time_stamp():day(), mon(), year(), hour(), min(), sec(){}
    friend std::ostream& operator<<(std::ostream& out, const Time_stamp& time);
};

//Временная струтура объекта опроса
struct ObjectTime
{
    Time_stamp start_pool;  //старт опроса
    Time_stamp end_pool;    //конец опроса
    Time_stamp next_pool;   //следущий опрос
    ObjectTime() : start_pool(), end_pool(), next_pool(){}
};

struct Interface
{
    INTERFACETYPE type;
    int number;
    Interface() : type(INTERFACETYPE::NONE), number(-1) {}
};

class ObjectAskue
{
    int _id;
    std::string _name_point;
    Interface _interface;
    ObjectTime _time;

public:
    ObjectAskue() : _id(), _name_point("unknown"), _interface(), _time() {}

};


class IBaseParser
{
public:
    virtual void parse(const std::string& log) = 0;
    virtual ~IBaseParser(){}
};

class ParseLogSrv : public IBaseParser
{
    std::vector<std::string> _record;
    PotokolLogSrv protocol;

    std::pair<bool, std::size_t> is_pollingPoints(const std::string& log) const;

    std::pair<bool, std::size_t> is_pointsPolling(const std::string& log) const;

    int getId(const std::string&log, std::size_t pos) const;

    std::pair<bool, const std::string> getName(const std::string& log) const;
    
    std::pair<bool, const std::string> findTime(const std::string& log) const;

    Time_stamp convertFindTime(const std::string& time) const;

    bool brokeRecord(const std::string& log);

public:

    void parse(const std::string& log) override;

    ~ParseLogSrv(){}
    
};

