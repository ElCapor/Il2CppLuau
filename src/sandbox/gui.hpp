#ifndef GUI_HPP
#define GUI_HPP
#include "imgui.h"
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_sdlrenderer2.h>
#include <SDL.h>
#include "../ui/widget.hpp"
#include "../utils/double_buffer.hpp"
/*
* UI Manager for the sandbox app
*/
class ImGuiManager
{
public:
    ImGuiManager() {};
    void Init(SDL_Window* window, SDL_Renderer* renderer);

    void ProcessEvent(const SDL_Event* event);

    void Render(SDL_Window *window, SDL_Renderer *renderer);
    
    void Cleanup();

    void AddWidget(Widget* widget);

private:
    ImVec2 DisplayFramebufferScale = {0,0};
    DoubleBuffer<Widget*> m_Widgets;
    int w_idx = -1;
};

#endif