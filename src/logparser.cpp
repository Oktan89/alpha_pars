#include <vector>
#include "logparser.h"



void ParseLogSrv::parse(const std::string& log)
{
    if (brokeRecord(log))
    {
        for (const auto &br : _record)
        {
            //Поиск времени для примера!!!!!
            std::size_t pos = br.find(protocol.head);
            if (br.npos != pos)
            {
                std::size_t pos_start = br.find(protocol.sbL);
                std::size_t pos_end = br.find(protocol.sbR, pos_start);
                if(pos_start == br.npos)
                {
                   pos_start = br.find(protocol.marks);
                   pos_end = br.find(protocol.marks, pos_start);
                }
                Time_stamp t = convertFindTime(br.substr(pos_start + 1, pos_end - pos_start - 1));
                pcout{} <<t.day<<"/"<<t.mon<<"/"<<t.year<<" "<<t.hour<<":"<<t.min<<":"<<t.sec<<"\n";
            }
            
        }
    }
}

Time_stamp ParseLogSrv::convertFindTime(const std::string& time)
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