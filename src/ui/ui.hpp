#ifndef UI_HPP
#define UI_HPP
#include <functional>
#include <vector>
#include "widget.hpp"
#include <mutex>
namespace ui
{
    void InitUi();
    void HookDX11();
    void RegisterWidgets();
    void RegisterWidget(Widget* widget);

    extern std::vector<Widget*> m_Widgets;
    extern int ui_idx;
}

#endif