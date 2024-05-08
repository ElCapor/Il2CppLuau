#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
#include "Lua/LuaVM.hpp"
#include <polyhook/polyhook2/Detour/x64Detour.hpp>
#include <polyhook/polyhook2/Detour/ILCallback.hpp>
#include <algorithm>

/*
local f = function(var :int) :int
return 100
end
proto_inspector(f)*/
// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Console::get()->open();
    LuaVM::get()->InitVM();
    lua_State* L = LuaVM::get()->LuaState();
    lua_pushcfunction(L, proto_inspector, "proto_inspector");
    lua_setglobal(L, "proto_inspector");
    App::get()->GetGuiManager().AddWidget(new ExecutorWidget());
    App::get()->Run();
    return 0;
}
