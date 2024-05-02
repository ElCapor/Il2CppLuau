#include "il2cpp_bridge.h"
#include "lualib.h"
#include "lua.h"
#include "../../utils/console/console.hpp"
#include <UnityResolve/UnityResolve.hpp>

#define ASSEMBLY_MT_NAME "assembly.mt"
#define IL2CPP_MT_NAME "il2cpp.mt"
#define CLASS_MT_NAME "class.mt"
#define FIELD_MT_NAME "field.mt"
#define METHOD_MT_NAME "method.mt"


int index_field(lua_State* L)
{
    return 0;
}

static const luaL_Reg field_m[]
{
    {"__index", index_field},{NULL, NULL}
};

int index_method(lua_State* L)
{
    const char* key = lua_tostring(L, -1);
    if (lua_isuserdata(L, -2))
    {
        if (strcmp(key, "name") == 0)
        {
            auto cls = (UnityResolve::Method*)lua_tolightuserdata(L, -2);
            lua_pushstring(L, cls->name.c_str());
            return 1;
        }
    }
    return 0;
}

static const luaL_Reg method_m[]
{
    {"__index", index_method}, {NULL, NULL}
};

int newindex_class(lua_State* L)
{
    return 0;
}

int index_class(lua_State* L)
{
    const char* key = lua_tostring(L, -1);
    if (lua_isuserdata(L, -2))
    {
        if (strcmp(key, "name") == 0)
        {
            auto cls = (UnityResolve::Class*)lua_tolightuserdata(L, -2);
            lua_pushstring(L, cls->name.c_str());
            return 1;
        } else if (strcmp(key, "methods") == 0)
        {
            auto cls = (UnityResolve::Class*)lua_tolightuserdata(L, -2);
            int idx=1;
            lua_newtable(L);
            for (auto& pMethod : cls->methods)
            {
                lua_pushlightuserdata(L, pMethod);
                luaL_getmetatable(L, METHOD_MT_NAME);
                lua_setmetatable(L, -2);
                lua_rawseti(L, -2, idx);
                idx++;
            }
            return 1;
        }
    }
    return 0;
}

static const luaL_Reg class_m[] = {
    {"__index", index_class}, {"__newindex", newindex_class},{NULL, NULL}
};

int newindex_assembly(lua_State* L)
{   
    return 0;
}

int index_assembly(lua_State *L)
{   
    const char* key = lua_tostring(L, -1);
    if (lua_islightuserdata(L, -2))
    {
        auto assembly = (UnityResolve::Assembly*)lua_tolightuserdata(L, -2);
        if (strcmp(key, "name") == 0)
        {
            if (assembly)
            {
                lua_pushstring(L, assembly->name.c_str());
                return 1;
            } else {
                return 0;
            }
        } else if (strcmp(key, "classes") == 0)
        {
            int idx=1;
            lua_newtable(L);
            for (auto& pClass : assembly->classes)
            {
                lua_pushlightuserdata(L, pClass);
                luaL_getmetatable(L, CLASS_MT_NAME);
                lua_setmetatable(L, -2);
                lua_rawseti(L, -2, idx);
                idx++;
            }
            return 1;
        }
    }
    return 0;
}

int get_assembly(lua_State* L)
{
    Console::get()->log("-1 -> ", luaL_typename(L, -1));
    Console::get()->log("-2 -> ", luaL_typename(L, -2));
    return 0;
}

static const luaL_Reg assembly_m[]
{
    {"__newindex", newindex_assembly}, {"__index", index_assembly},{"get", get_assembly}, {NULL, NULL}
};

int newindex_il2cpp(lua_State* L)
{
    return 0;
}
int index_il2cpp(lua_State* L)
{
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
    create_lua_mt(L, CLASS_MT_NAME, class_m);
    create_lua_mt(L, FIELD_MT_NAME, field_m);
    create_lua_mt(L, METHOD_MT_NAME, method_m);
    create_lua_mt(L, IL2CPP_MT_NAME, il2cpp_m);
    lua_newtable(L);
    luaL_getmetatable(L, IL2CPP_MT_NAME);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "il2cpp");
    return 0;
}