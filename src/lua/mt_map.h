#ifndef mt_map_hpp
#define mt_map_hpp
#include <map>
#include <string>

#define MT_MAP(class, mt_name) {typeid(class).name(), mt_name}
#define INSERT_MT(class, mt_name) typeMetatableMap()[typeid(class).name()] = mt_name;


std::map<std::string,std::string>& typeMetatableMap();
std::map<std::string, std::string>& metatableMap();

// best solution to access any metatable of any type
template <typename T>
std::string getMetatable()
{
    auto type_mt_map = typeMetatableMap();
    auto it = type_mt_map.find(typeid(T).name());
    if (it != type_mt_map.end()) {
        return it->second;
    } else {
        return "";
    }
}

std::string getMetatable(std::string name);


#endif