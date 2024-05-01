#ifndef dbg
#define dbg
#define DEBUG_MODE
// debug utils 
#include <Windows.h>
#include <iostream>
#include "colors.hpp"
#include "../singleton.hpp"
// debug console class with colors
class Console : public Singleton<Console>
{
protected:
    template <typename T>
    void log_argument(T t) {
        std::cout << t << " ";
    }
public:
    void open()
    {
        AllocConsole();
        FILE *f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONIN$", "r", stdin);
    }
    template <typename... Args>
    void log(Args&&... args) {
        std::cout << dye::green("[LOG] ");
        int dummy[] = { 0, ((void)log_argument(std::forward<Args>(args)),0)... };
        std::cout << std::endl;
    }

    template <typename... Args>
    void warn(Args&&... args) {
        std::cout << dye::yellow("[WARNING] ");
        int dummy[] = { 0, ((void)log_argument(std::forward<Args>(args)),0)... };
        std::cout << std::endl;
    }

    template <typename... Args>
    void error(Args&&... args) {
        std::cout << dye::red("[ERROR] ");
        int dummy[] = { 0, ((void)log_argument(std::forward<Args>(args)),0)... };
        std::cout << std::endl;
    }
    
#ifdef DEBUG_MODE
    template <typename... Args>
    void debug(Args&&... args) {

        std::cout << dye::aqua("[DEBUG] ");

        int dummy[] = { 0, ((void)log_argument(std::forward<Args>(args)),0)... };
        std::cout << std::endl;
    }
#else
    template <typename... Args>
    void debug(Args&&... args) {
        std::cout << std::endl;
    }
#endif


};

#endif // !dbg
