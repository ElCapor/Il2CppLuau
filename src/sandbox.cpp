#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
#include "Lua/LuaVM.hpp"
#include <polyhook/polyhook2/Detour/x64Detour.hpp>
#include <polyhook/polyhook2/Detour/ILCallback.hpp>
#include <algorithm>
#include <polyhook/asmjit/src/asmjit/asmjit.h>
#include "Lua/lextra.h"
#include "jit/CTypes.hpp"

// Jit construction runtime
asmjit::JitRuntime m_Runtime;

int type_stack(lua_State* L)
{
    // Check if there is exactly 1 argument
    if (lua_gettop(L) != 1) {
        luaL_error(L, "Function expects exactly 1 argument");
        return 0;
    }

    // Get the type of the argument
    int type = lua_type(L, 1);

    // Print the type to stdout
    const char* typeName = lua_typename(L, type);
    printf("Type of argument: %s\n", typeName);

    // No return value
    return 0;
}


int get_jit(lua_State* L)
{
    int n = lua_gettop(L);
    for (int i =1; i <=n; i++)
    {
        printf("%s\n", lua_type(L, i));
    }
    return 0;
}

/*
local f = function(var :int) :int
return 100
end
proto_inspector(f)*/

/*
* 
* */
// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Console::get()->open();
    LuaVM::get()->InitVM();
    lua_State* L = LuaVM::get()->LuaState();
    App::get()->GetGuiManager().AddWidget(new ExecutorWidget());
    lua_pushcfunction(L, type_stack, "type_stack");
    lua_setglobal(L, "type_stack");
    lua_pushcfunction(L, get_jit, "get_jit");
    lua_setglobal(L, "get_jit");
    App::get()->Run();
    return 0;
}
