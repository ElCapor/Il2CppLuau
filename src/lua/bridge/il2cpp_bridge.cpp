#include "il2cpp_bridge.h"
#include "lualib.h"
#include "lua.h"
#include "../../utils/console/console.hpp"

#define ASSEMBLY_MT_NAME "assembly.mt"
#define IL2CPP_MT_NAME "il2cpp.mt"
int newindex_assembly(lua_State* L)
{   
    return 0;
}

int index_assembly(lua_State *L)
{
    Console::get()->log("-1 -> ", luaL_typename(L, -1));
    Console::get()->log("-2 -> ", luaL_typename(L, -2));

    return 0;
}

int new_assembly(lua_State* L)
{
    return 1;
}
static const luaL_Reg assembly_m[]
{
    {"__newindex", newindex_assembly}, {"__index", index_assembly}, {NULL, NULL}
};

int newindex_il2cpp(lua_State* L)
{
    return 0;
}
int index_il2cpp(lua_State* L)
{
    return 0;
}
    
static const luaL_Reg il2cpp_m[] =
{
    {"__newindex", newindex_il2cpp}, {"__index", index_il2cpp}, {NULL, NULL}
};

void create_lua_mt(lua_State* L, const char* mt_name, const luaL_Reg* m_reg)
{
    luaL_newmetatable(L, mt_name);

    for (const luaL_Reg* method = m_reg;method->name != NULL; method++)
    {
        lua_pushstring(L, method->name);
        lua_pushcfunction(L, method->func, method->name);
        lua_settable(L, -3);
    }
}

int lua_bindings::register_il2cpp_bridge(lua_State* L)
{
    create_lua_mt(L, ASSEMBLY_MT_NAME, assembly_m);
    lua_newtable(L);
    luaL_getmetatable(L, ASSEMBLY_MT_NAME);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "assembly");
    return 0;
}