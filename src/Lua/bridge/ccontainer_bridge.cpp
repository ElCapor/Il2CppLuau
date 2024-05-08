#include "ccontainer_bridge.h"
#include <typeinfo>
#include "../../jit/CTypes.hpp"
#include <lualib.h>
#include <luacode.h>
#include "../mt_map.h"
#include "../lextra.h"

void bindMt()
{
    INSERT_MT(jit::CContainer, "ccontainer.mt");
    INSERT_MT(jit::VoidContainer, "void.mt");
};

int void_type(lua_State* L)
{
    auto v = luaL_checklightuserdata<jit::VoidContainer>(L, -2);
    if (v)
    {
        lua_pushinteger(L, static_cast<int>(v->m_CType));
        return 1;
    }
    return 0;
}

int void_value(lua_State* L)
{
    auto v = luaL_checklightuserdata<jit::VoidContainer>(L, -2);
    if (v)
    {
        lua_pushinteger(L, reinterpret_cast<intptr_t>(v->GetValue()));
        return 1;
    }
    return 0;
}

const luaL_Reg void_f[]
{
    {"value", void_value}, {"type", void_type},{NULL, NULL}
};

int void_index(lua_State* L)
{
    const char* key = lua_tostring(L, -1);
    auto ret = indexFields(L, void_f, key);
    if (ret.second)
        return ret.first;

    return 0;
}

static const luaL_Reg void_m[] = 
{
    {"__index", void_index},{NULL, NULL}
};

int void_new(lua_State* L)
{
    int ptr_val = lua_tointeger(L, -1);
    void* ptr = reinterpret_cast<void*>(ptr_val);
    jit::VoidContainer* cntr = new jit::VoidContainer();
    cntr->SetValue(ptr);
    luaL_pushlightuserdata<jit::VoidContainer>(L, cntr);
    return 1;
}

void create_void_tbl(lua_State* L)
{
    lua_newtable(L);
    lua_pushcfunction(L, void_new, "void.new");
    lua_setfield(L, -2, "new");
    lua_setglobal(L, "void");
}

int lua_bindings::register_ccontainer_bridge(lua_State* L)
{
    bindMt();
    create_lua_mt(L, getMetatable<jit::VoidContainer>().c_str(), void_m);
    create_void_tbl(L);
    return 0;
}
