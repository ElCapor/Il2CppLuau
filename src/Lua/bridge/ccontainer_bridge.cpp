#include "ccontainer_bridge.h"
#include <typeinfo>
#include "../../jit/CTypes.hpp"
#include <lualib.h>
#include <luacode.h>
#include "../mt_map.h"
#include "../lextra.h"

void bindContainerMt()
{
    INSERT_MT(jit::CContainer, "ccontainer.mt");
    INSERT_MT(jit::VoidPtrContainer, "voidptr.mt");
};

int voidptr_type(lua_State* L)
{
    auto v = luaL_checklightuserdata<jit::VoidPtrContainer>(L, -2);
    if (v)
    {
        lua_pushinteger(L, static_cast<int>(v->m_CType));
        return 1;
    }
    return 0;
}

int voidptr_value(lua_State* L)
{
    auto v = luaL_checklightuserdata<jit::VoidPtrContainer>(L, -2);
    if (v)
    {
        lua_pushinteger(L, reinterpret_cast<intptr_t>(v->GetValue()));
        return 1;
    }
    return 0;
}

const luaL_Reg voidptr_f[]
{
    {"value", voidptr_value}, {"type", voidptr_type},{NULL, NULL}
};

int voidptr_index(lua_State* L)
{
    const char* key = lua_tostring(L, -1);
    auto ret = indexFields(L, voidptr_f, key);
    if (ret.second)
        return ret.first;

    return 0;
}

static const luaL_Reg voidptr_m[] = 
{
    {"__index", voidptr_index},{NULL, NULL}
};

int voidptr_new(lua_State* L)
{
    int ptr_val = lua_tointeger(L, -1);
    void* ptr = reinterpret_cast<void*>(ptr_val);
    jit::VoidPtrContainer* cntr = new jit::VoidPtrContainer();
    cntr->SetValue(ptr);
    luaL_pushlightuserdata<jit::VoidPtrContainer>(L, cntr);
    return 1;
}

int voidptr_ctype(lua_State* L)
{
    if (lua_gettop(L) > 0)
    {
        luaL_error(L, "No arguments expected");
        return 0;
    }
    lua_pushinteger(L, static_cast<int>(jit::CType::CType_Void));
    return 1;
}

void create_voidptr_tbl(lua_State* L)
{
    lua_newtable(L);
    lua_pushcfunction(L, voidptr_new, "voidptr.new");
    lua_setfield(L, -2, "new");
    lua_pushcfunction(L, voidptr_ctype, "voidptr.ctype");
    lua_setfield(L, -2, "ctype");
    lua_setglobal(L, "void");
}

int lua_bindings::register_ccontainer_bridge(lua_State* L)
{
    bindContainerMt();
    create_lua_mt(L, getMetatable<jit::VoidPtrContainer>().c_str(), voidptr_m);
    create_voidptr_tbl(L);
    return 0;
}
