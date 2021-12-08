#pragma once
#include <string>
#include <vector>
#include <utility>
#include <ostream>
#include <mutex>
#include <memory>
#include "pcout.h"
#include <database.h>
#include "textprotocol.h"

//Тип интерфейса опроса
enum class INTERFACETYPE
{
    COM,
    TCP,
    NONE
};

enum class STATUSOBJECT
{
    START_POLL,
    STOP_POLL,
    WAIT_START_POLL,
    UNKNOWN
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
    STATUSOBJECT _status;
    mutable std::mutex _mutex;
    friend std::ostream& operator<<(std::ostream& out, const ObjectAskue& askue);
public:
    ObjectAskue() : 
    _id(), _name_point("unknown"), _interface(), _time(), _status(STATUSOBJECT::UNKNOWN) {}
    
    ObjectAskue(const ObjectAskue& object);
    
    ObjectAskue& operator=(const ObjectAskue& other);
    
    ~ObjectAskue(){}

    void setId(int id);
    int getId() const;

    void setName(const std::string& name);
    std::string getName() const;

    void setTime(const STATUSOBJECT status, const Time_stamp& time);
    Time_stamp getStatusTime() const;

    void setInterface(const Interface& port);
    Interface getInterface() const;
    std::string getInetrface_s() const;

    STATUSOBJECT getStatus() const;
    std::string getStatus_s() const;

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
    std::shared_ptr<Database> _data;

    std::pair<bool, std::size_t> is_pollingPoints(const std::string& log) const;

    std::pair<bool, std::size_t> is_pointsPolling(const std::string& log) const;

    //Вызввать только после is_pollingPoints или is_pointsPolling
    int getId(const std::string&log, std::size_t pos) const;

    std::pair<bool, STATUSOBJECT> pollingStatusStartStop(const std::string& log, std::size_t pos = 0) const;

    std::pair<bool, Interface> getPort(const std::string& log, std::size_t pos = 0) const;

    std::pair<bool, const std::string> getName(const std::string& log) const;
    
    std::pair<bool, const std::string> findTime(const std::string& log) const;

    Time_stamp convertFindTime(const std::string& time) const;

    bool splitRecord(const std::string& log);
    
public:
    ParseLogSrv(std::shared_ptr<Database> data) : _data(data){}
    void parse(const std::string& log) override;

    ~ParseLogSrv(){}
    
};

