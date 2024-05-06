#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    App::get()->GetGuiManager().AddWidget(new ExecutorWidget());
    App::get()->Run();
    return 0;
}
