#include "mt_map.h"

std::map<std::string,std::string>& typeMetatableMap()
{
    static std::map<std::string, std::string> type_mt_map = {
        
    };

    return type_mt_map;
}

std::map<std::string, std::string>& metatableMap()
{
    static std::map<std::string, std::string> mt_map = {
        {"il2cpp", "il2cpp"}
    };

    return mt_map;
}

std::string getMetatable(std::string name)
{
    auto mt_map = metatableMap();
    auto it = mt_map.find(name);
    if (it != mt_map.end()) {
        return it->second;
    } else {
        return "";
    }
}