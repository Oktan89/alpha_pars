#include <iomanip>
#include "logparser.h"


void ParseLogSrv::parse(const std::string& log)
{
    std::size_t pos = log.find("***");
    if (log.npos != pos)
    {
        std::size_t pos_start = log.find('[');
        std::size_t pos_end = log.find(']', pos_start);
        convertFindTime(log.substr(pos_start + 1, pos_end - pos_start - 1));
    }
   // pcout{} << pos << log << "\n";
}

std::tm ParseLogSrv::convertFindTime(const std::string& time)
{
    std::tm t;
    t.tm_mday = std::stoi(time.substr(0, 2));
    t.tm_mon = std::stoi(time.substr(3, 2));
    t.tm_year = std::stoi(time.substr(6, 4)) - 1900;
    t.tm_hour = std::stoi(time.substr(11, 2));
    t.tm_min = std::stoi(time.substr(14, 2));
    t.tm_sec = std::stoi(time.substr(17, 2));
    std::time_t t_mk = std::mktime(&t);
    t = *std::localtime(&t_mk);

    pcout{} << "local: " << std::put_time(&t, "%c %Z") << '\n';
    return t;
}