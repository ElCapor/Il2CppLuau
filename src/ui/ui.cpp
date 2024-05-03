#include <kiero/d3d11Hook.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include "../globals/globals.hpp"
#include <iostream>
#include "ui.hpp"
extern auto ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;
std::vector<Widget*> ui::m_Widgets = {};
void ui::InitUi()
{
    if (!GlobalsManager::get()->IsGuiReady())
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplWin32_Init(dx_hook::Hk11::GetHwnd());
        ImGui_ImplDX11_Init(dx_hook::Hk11::GetDevice(), dx_hook::Hk11::GetContext());
        dx_hook::Hk11::SetWndProc([](const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> char
                                  {
            POINT mPos;
            GetCursorPos(&mPos);
            ScreenToClient(dx_hook::Hk11::GetHwnd(), &mPos);
            ImGui::GetIO().MousePos.x = static_cast<float>(mPos.x);
            ImGui::GetIO().MousePos.y = static_cast<float>(mPos.y);
            ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

            switch (msg) {
                case WM_KEYDOWN:
                    if (wParam == VK_DELETE) {
                        if (GlobalsManager::get()->ShowGui()) GlobalsManager::get()->showGui = false;
                        else GlobalsManager::get()->ShowGui() = true;
                    }
                    break;
                case WM_KEYUP: break;
            }

            if (GlobalsManager::get()->ShowGui()) return false;

            return true; });

        auto HexToRGBA = [](const std::string &Hex)
        {
            int r, g, b, a;
            sscanf_s(Hex.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
            const ImVec4 color{(static_cast<float>(r) / 255), (static_cast<float>(g) / 255), (static_cast<float>(b) / 255), (static_cast<float>(a) / 255)};
            return color;
        };

        auto &styles = ImGui::GetStyle();

        // Colors
        auto colors = styles.Colors;
        colors[ImGuiCol_Border] = HexToRGBA("0C846ED5");
        colors[ImGuiCol_BorderShadow] = HexToRGBA("00000000");
        colors[ImGuiCol_Button] = HexToRGBA("0D9F9D9F");
        colors[ImGuiCol_ButtonActive] = HexToRGBA("076B3A94");
        colors[ImGuiCol_ButtonHovered] = HexToRGBA("0CAD4FCA");
        colors[ImGuiCol_CheckMark] = HexToRGBA("E6E6E680");
        colors[ImGuiCol_ChildBg] = HexToRGBA("00000045");
        colors[ImGuiCol_DragDropTarget] = HexToRGBA("333333FF");
        colors[ImGuiCol_FrameBg] = HexToRGBA("00000066");
        colors[ImGuiCol_FrameBgActive] = HexToRGBA("0D7F33B0");
        colors[ImGuiCol_FrameBgHovered] = HexToRGBA("09818B66");
        colors[ImGuiCol_Header] = HexToRGBA("0297959F");
        colors[ImGuiCol_HeaderActive] = HexToRGBA("07834ACC");
        colors[ImGuiCol_HeaderHovered] = HexToRGBA("00B8588A");
        colors[ImGuiCol_MenuBarBg] = HexToRGBA("069981CC");
        colors[ImGuiCol_ModalWindowDimBg] = HexToRGBA("3333335A");
        colors[ImGuiCol_NavHighlight] = HexToRGBA("7373E6CC");
        colors[ImGuiCol_NavWindowingDimBg] = HexToRGBA("CCCCCC33");
        colors[ImGuiCol_NavWindowingHighlight] = HexToRGBA("FFFFFFB3");
        colors[ImGuiCol_PlotHistogram] = HexToRGBA("E6B300FF");
        colors[ImGuiCol_PlotHistogramHovered] = HexToRGBA("FF9900FF");
        colors[ImGuiCol_PlotLines] = HexToRGBA("FFFFFFFF");
        colors[ImGuiCol_PlotLinesHovered] = HexToRGBA("E6B300FF");
        colors[ImGuiCol_PopupBg] = HexToRGBA("1D1D24EB");
        colors[ImGuiCol_ResizeGrip] = HexToRGBA("FFFFFF1A");
        colors[ImGuiCol_ResizeGripActive] = HexToRGBA("C7D2FFE6");
        colors[ImGuiCol_ResizeGripHovered] = HexToRGBA("C7D2FF99");
        colors[ImGuiCol_ScrollbarBg] = HexToRGBA("33404D99");
        colors[ImGuiCol_ScrollbarGrab] = HexToRGBA("0C864E65");
        colors[ImGuiCol_ScrollbarGrabActive] = HexToRGBA("02B3916F");
        colors[ImGuiCol_ScrollbarGrabHovered] = HexToRGBA("05925966");
        colors[ImGuiCol_Separator] = HexToRGBA("1CA09A7E");
        colors[ImGuiCol_SeparatorActive] = HexToRGBA("0099B1FF");
        colors[ImGuiCol_SeparatorHovered] = HexToRGBA("048897FF");
        colors[ImGuiCol_SliderGrab] = HexToRGBA("FFFFFF4D");
        colors[ImGuiCol_SliderGrabActive] = HexToRGBA("04882F99");
        colors[ImGuiCol_Tab] = HexToRGBA("18999F60");
        colors[ImGuiCol_TabActive] = HexToRGBA("038B4CD7");
        colors[ImGuiCol_TabHovered] = HexToRGBA("1E784BCC");
        colors[ImGuiCol_TabUnfocused] = HexToRGBA("FFFFFF00");
        colors[ImGuiCol_TabUnfocusedActive] = HexToRGBA("5A5AA700");
        colors[ImGuiCol_TableBorderLight] = HexToRGBA("FFFFFF00");
        colors[ImGuiCol_TableBorderStrong] = HexToRGBA("00014000");
        colors[ImGuiCol_TableHeaderBg] = HexToRGBA("2E8D89FF");
        colors[ImGuiCol_TableRowBg] = HexToRGBA("3E72769A");
        colors[ImGuiCol_TableRowBgAlt] = HexToRGBA("154D3E9B");
        colors[ImGuiCol_Text] = HexToRGBA("E6E6E6FF");
        colors[ImGuiCol_TextDisabled] = HexToRGBA("999999FF");
        colors[ImGuiCol_TextSelectedBg] = HexToRGBA("00A87E5A");
        colors[ImGuiCol_TitleBg] = HexToRGBA("00998D8A");
        colors[ImGuiCol_TitleBgActive] = HexToRGBA("008D556B");
        colors[ImGuiCol_TitleBgCollapsed] = HexToRGBA("27B6C14A");
        colors[ImGuiCol_WindowBg] = HexToRGBA("00000096");

        // Styles
        styles.Alpha = 1.0;
        styles.AntiAliasedFill = true;
        styles.AntiAliasedLines = true;
        styles.AntiAliasedLinesUseTex = true;
        styles.ButtonTextAlign = ImVec2(0.5, 0.5);
        styles.CellPadding = ImVec2(4.0, 2.0);
        styles.ChildBorderSize = 1.0;
        styles.ChildRounding = 0.0;
        styles.CircleTessellationMaxError = 0.30000001192092896;
        styles.ColorButtonPosition = 1;
        styles.ColumnsMinSpacing = 6.0;
        styles.CurveTessellationTol = 1.25;
        styles.DisabledAlpha = 0.6000000238418579;
        styles.DisplaySafeAreaPadding = ImVec2(3.0, 3.0);
        styles.DisplayWindowPadding = ImVec2(19.0, 19.0);
        styles.FrameBorderSize = 0.0;
        styles.FramePadding = ImVec2(4.0, 3.0);
        styles.FrameRounding = 0.0;
        styles.GrabMinSize = 10.0;
        styles.GrabRounding = 0.0;
        styles.IndentSpacing = 21.0;
        styles.ItemInnerSpacing = ImVec2(4.0, 4.0);
        styles.ItemSpacing = ImVec2(8.0, 4.0);
        styles.LogSliderDeadzone = 4.0;
        styles.MouseCursorScale = 1.0;
        styles.PopupBorderSize = 0.0;
        styles.PopupRounding = 0.0;
        styles.ScrollbarRounding = 0.0;
        styles.ScrollbarSize = 14.0;
        styles.SelectableTextAlign = ImVec2(0.0, 0.0);
        styles.TabBorderSize = 0.0;
        styles.TabMinWidthForCloseButton = 0.0;
        styles.TabRounding = 0.0;
        styles.TouchExtraPadding = ImVec2(0.0, 0.0);
        styles.WindowBorderSize = 0.0;
        styles.WindowMenuButtonPosition = 0;
        styles.WindowMinSize = ImVec2(32.0, 32.0);
        styles.WindowPadding = ImVec2(8.0, 8.0);
        styles.WindowRounding = 0.0;
        styles.WindowTitleAlign = ImVec2(0.0, 0.5);
        GlobalsManager::get()->IsGuiReady() = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (GlobalsManager::get()->ShowGui())
    {
        for (auto& widget : m_Widgets)
        {
            if (!widget->IsInit())
            {
                widget->Init();
                widget->IsInit() = true;
            }
            widget->Render();
        }
    }
    ImGui::EndFrame();
    ImGui::Render();
    dx_hook::Hk11::GetContext()->OMSetRenderTargets(1, dx_hook::Hk11::GetTargetView(), nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

};

void ui::HookDX11()
{
    dx_hook::Hk11::Build(ui::InitUi);
};

#include "widgets/ExecutorWidget.hpp"
void ui::RegisterWidgets()
{
    m_Widgets.push_back(ExecutorWidget::get());
    int idx = 0;
    for (auto& widget : m_Widgets)
    {
        widget->setId(idx);
        idx++;
    }
}