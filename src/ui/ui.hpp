#ifndef UI_HPP
#define UI_HPP
#include <functional>
#include <vector>
#include "widget.hpp"
namespace ui
{
    void InitUi();
    void HookDX11();
    void RegisterWidgets();
    extern std::vector<Widget*> m_Widgets;
}

#endif