#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include "../utils/singleton.hpp"
#define AddGlobal(type, global_name) type global_name; \
type& Get##global_name() {return global_name;} 

class GlobalsManager : public Singleton<GlobalsManager>
{
public:
    GlobalsManager(){};

    bool& IsGuiReady() {return isGuiReady;};
    bool& ShowGui() {return showGui;};
    HMODULE& HModule() {return hModule;};
    
    HMODULE hModule = 0;
    bool showGui = false;
    bool isGuiReady = false;
};

#undef AddGlobal

#endif