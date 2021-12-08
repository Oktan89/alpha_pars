#include <database.h>
#include "logparser.h"

void Database::setObject(ObjectAskue& askue)
{
    std::lock_guard<std::mutex> lg(_mx_map);
    auto it = _db.find(askue.getId());
    if (it != _db.end())
    {
        std::swap(it->second, askue); //Проверка имени происходит в коснтрукторе присваивания
        pcout{} << "Объект обновлен\n";
        showAskue(it->second);
    }
    else
    {
        auto obj = _db[askue.getId()] = askue;
        pcout{} << "Объект добавлен\n";
        showAskue(obj);
    }
}

void showAskue(const ObjectAskue& askue)
{
    pcout{} <<"[--------------------]\n";
    pcout{} <<"[ID  : "<< askue.getId() <<" ]\n";
    pcout{} <<"[NAME: "<< askue.getName()<<" ]\n";
    pcout{} <<"[STATUS: "<< askue.getStatus_s()<<" ]\n";
    switch (askue.getStatus())
    {
        case STATUSOBJECT::START_POLL:
            pcout{} <<"[TIME:"<< askue.getStatusTime()<<" ]\n";
            pcout{} <<"[PORT: "<< askue.getInetrface_s()<<" ]\n";
            break;
        case STATUSOBJECT::STOP_POLL:
            pcout{} <<"[TIME:"<< askue.getStatusTime()<<" ]\n";
            break;
        case STATUSOBJECT::WAIT_START_POLL:
            pcout{} <<"[TIME:"<< askue.getStatusTime()<<" ]\n";
            break;
        default:
            break;
    }
    pcout{} <<"[--------------------]\n";
}