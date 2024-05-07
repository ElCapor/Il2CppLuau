#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
#include "Lua/LuaVM.hpp"

// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Console::get()->open();
    LuaVM::get()->InitVM();
    App::get()->GetGuiManager().AddWidget(new ExecutorWidget());
    App::get()->Run();
    return 0;
}
