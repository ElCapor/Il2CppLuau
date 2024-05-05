#ifndef UI_HPP
#define UI_HPP
#include <functional>
#include "../utils/double_buffer.hpp"
#include "widget.hpp"
#include <mutex>

namespace ui
{
    void InitUi();
    void HookDX11();
    void RegisterWidgets();
    void RegisterWidget(Widget* widget);

    extern DoubleBuffer<Widget*> m_Widgets;
    extern int ui_idx;
}

#endif