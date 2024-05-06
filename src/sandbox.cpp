#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    App::get()->Run();
    return 0;
}
