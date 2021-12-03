#include <vector>
#include "logparser.h"


std::ostream& operator<<(std::ostream& out, const Time_stamp& time)
{
    out << time.day<<"/"<<time.mon<<"/"<<time.year<<" "<<time.hour<<":"<<time.min<<":"<<time.sec<<"\n"; 
    return out;
}

void ParseLogSrv::parse(const std::string& log)
{
    ObjectAskue askue;
    if (splitRecord(log))
    {
        for (const auto &br : _record)
        {
            auto poll = is_pollingPoints(br);
            if(poll.first)
            {
                //pcout{} << getId(br, poll.second) << std::endl;//-1 error
                askue.setId(getId(br, poll.second));
                auto name = getName(br);
                if(name.first)
                    askue.setName(name.second);
                   // pcout{} << name.second << std::endl;
                auto find_t = findTime(br);
                if(find_t.first)
                {
                    auto timestamp = convertFindTime(find_t.second);
                    pcout{} << timestamp;
                }
            }
            else
            {
                auto poll = is_pointsPolling(br);
                if(poll.first)
                {
                    //pcout{} << getId(br, poll.second) << std::endl;
                    askue.setId(getId(br, poll.second));
                    auto find_t = findTime(br);
                    if(find_t.first)
                    {
                        auto timestamp = convertFindTime(find_t.second);
                        askue.setTime(STATUSOBJECT::WAIT_START_POLL, timestamp);
                        pcout{} << timestamp;
                    }
                }
            }
            _data->setObject(askue);
        }
    }
}

//Содержит строка {опрос точки}?
std::pair<bool, std::size_t> ParseLogSrv::is_pollingPoints(const std::string& log) const
{   
    std::size_t pos = log.find(protocol.poll_p);
    if(log.npos != pos)
        return std::make_pair(true, pos+12);//strlen
    return std::make_pair(false, pos);
}

//Содержит строка {точка опроса}?
std::pair<bool, std::size_t> ParseLogSrv::is_pointsPolling(const std::string &log) const
{
    std::size_t pos = log.find(protocol.p_poll);
    if (log.npos != pos)
        return std::make_pair(true, pos+13);
    return std::make_pair(false, pos);
}

//Поиск времени если найден true и ссылка на кусочек с временем
std::pair<bool, const std::string> ParseLogSrv::findTime(const std::string& log) const
{
    std::size_t pos = log.find(protocol.head);
    if (log.npos != pos)
    {
        std::size_t pos_start = log.find(protocol.sbL);
        std::size_t pos_end =log.find(protocol.sbR, pos_start);
        if (pos_start == log.npos)
        {
            pos_start = log.find(protocol.marks);
            pos_end = log.find(protocol.marks, pos_start);
        }
        return std::make_pair(true, log.substr(pos_start + 1, pos_end - pos_start - 1));
    }
    return std::make_pair(false, log);
}

int ParseLogSrv::getId(const std::string& log, std::size_t pos) const
{
    std::size_t pos_end = log.find_first_of(' ', pos);
    if(pos_end == log.npos)
        return -1;
    return std::stoi(log.substr(pos, pos_end - pos ));
}

std::pair<bool, const std::string> ParseLogSrv::getName(const std::string& log) const
{
    std::size_t pos_start = log.find_first_of(protocol.rbL);
    std::size_t pos_end = log.find_last_of(protocol.rbR);
    
    if(pos_start != log.npos || pos_end != log.npos)
    {
        ++pos_start;
        return std::make_pair(true, log.substr(pos_start, pos_end-pos_start));
    }
        
    return std::make_pair(false, log);
}

Time_stamp ParseLogSrv::convertFindTime(const std::string& time) const
{
    Time_stamp ts;
    
    ts.day = std::stoi(time.substr(0, 2));
    ts.mon = std::stoi(time.substr(3, 2));
    ts.year = std::stoi(time.substr(6, 4));
    ts.hour = std::stoi(time.substr(11, 2));
    ts.min = std::stoi(time.substr(14, 2));
    ts.sec = std::stoi(time.substr(17, 2));
    
    return ts;
}

bool ParseLogSrv::splitRecord(const std::string &log)
{
    //ищем первое вхождение ***
    std::size_t start_pos = log.find(protocol.head);
    //если нашли
    while (start_pos != log.npos)
    {
        //ищем следующее
        std::size_t end_pos = log.find(protocol.head, start_pos + 3);
        //если больше нет то записываем всю строку от start
        if (end_pos == log.npos)
        {
            _record.push_back(log.substr(start_pos));
            //и завершаем цикл
            start_pos = end_pos;
        }
        //если найдено следующее вхождение ***
        else
        {
            //записываем строку от start до end -1
           _record.push_back(log.substr(start_pos, end_pos - start_pos));
            //задаем следующее значение для поиска *** от end
            start_pos = end_pos;
        }
    }
    //For debug
    /* for(const auto& l : _record)
        pcout{} << l;*/
    return !_record.empty();
}

void ObjectAskue::setId(int id)
{
    std::lock_guard<std::mutex> lg(_mutex);
    _id = id;
}

int ObjectAskue::getId() const
{
    std::lock_guard<std::mutex> lg(_mutex);
    return _id;
}

void ObjectAskue::setName(const std::string& name)
{
    std::lock_guard<std::mutex> lg(_mutex);
    _name_point = name;
}

std::string ObjectAskue::getName() const
{
    std::lock_guard<std::mutex> lg(_mutex);
    return _name_point;
}

void ObjectAskue::setTime(const STATUSOBJECT status, const Time_stamp& time)
{
    std::lock_guard<std::mutex> lg(_mutex);

    switch (status)
    {
    case STATUSOBJECT::START_POLL:
        _time.start_pool = time;
        break;
    case STATUSOBJECT::STOP_POLL :
        _time.end_pool = time;
        break;
    
    case STATUSOBJECT::WAIT_START_POLL :
        _time.next_pool = time;
        break;
    
    case STATUSOBJECT::UNKNOWN :
        pcout{} <<"set time unknown\n";
        break;
    
    default:
        pcout{} <<"set time error\n";
        _status = STATUSOBJECT::UNKNOWN;
        break;
    }

    _status = status;
}

Time_stamp ObjectAskue::getStatusTime() const
{
    std::lock_guard<std::mutex> lg(_mutex);
    Time_stamp time{};

    switch (_status)
    {
    case STATUSOBJECT::START_POLL:
        time = _time.start_pool;
        break;
    case STATUSOBJECT::STOP_POLL :
        time = _time.end_pool;
        break;
    
    case STATUSOBJECT::WAIT_START_POLL :
        time = _time.next_pool;
        break;
    
    case STATUSOBJECT::UNKNOWN :
   
    default:
        pcout{} <<"get time error\n";
        break;
    }
    return time;
}

ObjectAskue::ObjectAskue(const ObjectAskue& object) :
 _id(object._id), _name_point(object._name_point), _interface(object._interface),
 _time(object._time), _status(object._status)
{

}

ObjectAskue& ObjectAskue::operator=(const ObjectAskue& other)
{
    if(this == &other)
        return *this;
    _id = other._id;
    _name_point = other._name_point;
    _interface = other._interface;
    _time = other._time;
    _status = other._status;
    return *this;
}