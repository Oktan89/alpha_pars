#include <database.h>
#include "logparser.h"

void Database::setObject(ObjectAskue& askue)
    {   
        std::lock_guard<std::mutex> lg(_mx_map);
        auto it = _db.find(askue.getId());
        if(it != _db.end())
        {
            std::swap(it->second, askue);
            //it->second.setName(askue.getName());//?????
            pcout{} << "Объект обновлен" << "\n";
            pcout{} << it->second << "\n";
        }
        else
        {
            auto obj =_db[askue.getId()] = askue;
            pcout{} << "Объект добавлен" << "\n";
            pcout{} << obj <<"\n";
        }
    }