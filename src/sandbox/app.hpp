#ifndef APP_HPP
#define APP_HPP
#include "../utils/singleton.hpp"
#include "gui.hpp"
#include <stdio.h>
#include <SDL.h>

class App : public Singleton<App>
{
public:

    App() {};
    void Initialize();

    void Run();

    void Shutdown();

    ImGuiManager& GetGuiManager() { return m_guiManager;}

private:
    bool m_initialized;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool m_shouldExit = false;
    ImGuiManager m_guiManager;
};

#endif