#include "gui.hpp"


void ImGuiManager::Init(SDL_Window *window, SDL_Renderer *renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    DisplayFramebufferScale = io.DisplayFramebufferScale;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void ImGuiManager::ProcessEvent(const SDL_Event *event) {
    ImGui_ImplSDL2_ProcessEvent(event);
}

void ImGuiManager::Render(SDL_Window *window, SDL_Renderer *renderer) {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    for (auto& widget : m_Widgets.getCurrentBuffer())
    {
        if (!widget->IsInit())
        {
            widget->Init();
            widget->IsInit() = true;
        }
        widget->Render();
    }

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(renderer, DisplayFramebufferScale.x, DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(255), (Uint8)(255), (Uint8)(255), (Uint8)(255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Cleanup() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::AddWidget(Widget *widget) {
    std::vector<Widget*> tmp = m_Widgets.getCurrentBuffer();
    widget->setId(w_idx);
    w_idx++;
    m_Widgets.swapBuffers();
    m_Widgets.push(widget);
    for (auto& item : tmp)
    {
        m_Widgets.push(item);
    }
}
