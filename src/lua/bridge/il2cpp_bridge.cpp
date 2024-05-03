#include "il2cpp_bridge.h"
#include "lualib.h"
#include "lua.h"
#include "../../utils/console/console.hpp"
#include <UnityResolve/UnityResolve.hpp>

#define ASSEMBLY_MT_NAME "assembly.mt"
#define IL2CPP_MT_NAME "il2cpp.mt"
int newindex_assembly(lua_State* L)
{   
    return 0;
}

int index_assembly(lua_State *L)
{
    if (lua_islightuserdata(L, -2))
    {
        auto assembly = (UnityResolve::Assembly*)lua_tolightuserdata(L, -2);
        lua_pushstring(L, assembly->name.c_str());
        return 1;
    }
    return 0;
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
    Console::get()->log("-1 -> ", lua_tostring(L, -1));
    Console::get()->log("-2 -> ", luaL_typename(L, -2));
    const char* key = luaL_checkstring(L, -1);
    if (strcmp(key, "get") == 0) {
        luaL_getmetatable(L, IL2CPP_MT_NAME);
        lua_getfield(L, -1, "get");
        return 1;
    } else if (strcmp(key, "assembly") == 0)
    {
        int idx=1;
        lua_newtable(L);
        for (auto& pAssembly : UnityResolve::assembly)
        {
            lua_pushlightuserdata(L, pAssembly);
            luaL_getmetatable(L, ASSEMBLY_MT_NAME);
            lua_setmetatable(L, -2);
            lua_rawseti(L, -2, idx);
            // lua setfield ?
            idx++;
        }
        return 1;
    }
    return 0;
}

int get_il2cpp(lua_State* L)
{
    const char* assembly_name = luaL_checkstring(L, -1);
    Console::get()->log("Assembly name -> ", assembly_name);
    lua_pushlightuserdata(L, UnityResolve::Get(assembly_name));
    luaL_getmetatable(L, ASSEMBLY_MT_NAME);
    lua_setmetatable(L, -2);
    return 1;
}
static const luaL_Reg il2cpp_m[] =
{
    {"__newindex", newindex_il2cpp}, {"__index", index_il2cpp},{"get", get_il2cpp}, {NULL, NULL}
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
    create_lua_mt(L, IL2CPP_MT_NAME, il2cpp_m);
    lua_newtable(L);
    luaL_getmetatable(L, IL2CPP_MT_NAME);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "il2cpp");
    return 0;
}