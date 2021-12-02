#pragma once
#include <string>
#include <map>
#include "pcout.h"
#include "textprotocol.h"

//��� ���������� ������
enum class INTERFACETYPE
{
    COM,
    TCP,
    NONE
};

//��������� ������� � ����� ��
struct Time_stamp
{
    int day;
    int mon;
    int year;
    int hour;
    int min;
    int sec;
    Time_stamp():day(), mon(), year(), hour(), min(), sec(){}
};

//��������� �������� ������� ������
struct ObjectTime
{
    Time_stamp start_pool;  //����� ������
    Time_stamp end_pool;    //����� ������
    Time_stamp next_pool;   //�������� �����
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
    Time_stamp convertFindTime(const std::string& time);
    bool brokeRecord(const std::string& log);

public:

    void parse(const std::string& log) override;

    ~ParseLogSrv(){}
    
};
