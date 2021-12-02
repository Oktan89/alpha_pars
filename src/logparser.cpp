#include <vector>
#include "logparser.h"


std::ostream& operator<<(std::ostream& out, const Time_stamp& time)
{
    out << time.day<<"/"<<time.mon<<"/"<<time.year<<" "<<time.hour<<":"<<time.min<<":"<<time.sec<<"\n"; 
    return out;
}

void ParseLogSrv::parse(const std::string& log)
{
    if (brokeRecord(log))
    {
        for (const auto &br : _record)
        {
            auto poll = is_pollingPoints(br);
            if(poll.first)
            {
                pcout{} << getId(br, poll.second) << std::endl;
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
                    pcout{} << getId(br, poll.second) << std::endl;
                    auto find_t = findTime(br);
                    if(find_t.first)
                    {
                        auto timestamp = convertFindTime(find_t.second);
                        pcout{} << timestamp;
                    }
                }
            }
        }
    }
}

//Содержит строка {опрос точки}?
std::pair<bool, std::size_t> ParseLogSrv::is_pollingPoints(const std::string& log) const
{   
    std::size_t pos = log.find(protocol.poll_p);
    if(log.npos != pos)
        return std::make_pair(true, pos+12);
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

int ParseLogSrv::getId(const std::string&log, std::size_t pos) const
{
    std::size_t pos_end = log.find(" ", pos);
    if(pos_end == log.npos)
        return -1;
    return std::stoi(log.substr(pos, pos_end));
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

bool ParseLogSrv::brokeRecord(const std::string &log)
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
           _record.push_back(log.substr(start_pos, end_pos - 1));
            //задаем следующее значение для поиска *** от end
            start_pos = end_pos;
        }
    }
    //For debug
     for(const auto& l : _record)
        pcout{} << l;
    return !_record.empty();
}