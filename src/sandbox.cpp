#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
#include "Lua/LuaVM.hpp"


#include <luau/VM/src/lobject.h>
#include <luau/VM/src/lapi.h>
#include <luau/VM/src/lstate.h>
int proto_inspector(lua_State* L)
{
    if (lua_isLfunction(L, -1))
    {
        const TValue* func = luaA_toobject(L, -1);
        Proto* proto = clvalue(func)->l.p;
        Console::get()->log("Proto : ", proto->numparams);
        for (int i = 0; i<proto->sizetypeinfo; i++)
        {
            Console::get()->log("Typeinfo ", proto->typeinfo[i]);
        }
    }
    return 0;
}


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
