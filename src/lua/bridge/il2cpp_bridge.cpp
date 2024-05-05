#include "il2cpp_bridge.h"
#include "lualib.h"
#include "lua.h"
#include "../../utils/console/console.hpp"
#include <UnityResolve/UnityResolve.hpp>
#include "../lextra.h"
#include "../mt_map.h"

#define ASSEMBLY_MT_NAME "assembly.mt"
#define IL2CPP_MT_NAME "il2cpp.mt"
#define CLASS_MT_NAME "class.mt"
#define FIELD_MT_NAME "field.mt"
#define METHOD_MT_NAME "method.mt"
#define TYPE_MT_NAME "type.mt"
#define ARG_MT_NAME "arg.mt"

/// @brief Bind all metatables of the bridge globally
void bindMt()
{
    INSERT_MT(UnityResolve::Assembly, ASSEMBLY_MT_NAME);
    INSERT_MT(UnityResolve::Class, CLASS_MT_NAME);
    INSERT_MT(UnityResolve::Method, METHOD_MT_NAME);
    INSERT_MT(UnityResolve::Field, FIELD_MT_NAME);
    INSERT_MT(UnityResolve::Type, TYPE_MT_NAME);
    INSERT_MT(UnityResolve::Method::Arg, ARG_MT_NAME);

}

int type_arg(lua_State* L)
{
    auto arg = luaL_checklightuserdata<UnityResolve::Method::Arg>(L, -2);
    if (arg != nullptr)
    {
        return luaL_pushlightuserdata<UnityResolve::Type>(L, arg->pType);
    }
    else {
        return 0;
    }
}

int name_arg(lua_State* L)
{
    auto arg = luaL_checklightuserdata<UnityResolve::Method::Arg>(L, -2);
    if (arg != nullptr)
    {
        lua_pushstring(L, arg->name.c_str());
        return 1;
    }
    else {
        return 0;
    }
}

static const luaL_Reg arg_fields[]
{
    {"name", name_arg}, {"type", type_arg},{NULL, NULL}
};

int index_arg(lua_State* L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, arg_fields, key);
    if (ret.second)
        return ret.first;
    return 0;
}
static const luaL_Reg arg_m[]
{
    {"__index", index_arg}, {NULL, NULL}
};

int name_type(lua_State* L)
{
    auto type = luaL_checklightuserdata<UnityResolve::Type>(L, -2);
    if (type != nullptr)
    {
        lua_pushstring(L, type->name.c_str());
        return 1;
    }
    return 0;
}
static const luaL_Reg type_fields[]
{
    {"name", name_type},{NULL,NULL}
};

int index_type(lua_State* L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, type_fields, key);
    if (ret.second)
        return ret.first;
    return 0;
}

static const luaL_Reg type_m[]
{
    {"__index", index_type},{NULL, NULL}
};

int field_static(lua_State* L)
{
    auto field = luaL_checklightuserdata<UnityResolve::Field>(L, -2);
    if (field)
    {
        lua_pushboolean(L, field->static_field);
        return 1;
    }
    return 0;
}

int field_offset(lua_State* L)
{
    auto field = luaL_checklightuserdata<UnityResolve::Field>(L, -2);
    if (field)
    {
        lua_pushinteger(L, field->offset);
        return 1;
    }
    return 0;
}

int field_class(lua_State* L)
{
    auto field = luaL_checklightuserdata<UnityResolve::Field>(L, -2);
    if (field)
    {
        return luaL_pushlightuserdata<UnityResolve::Class>(L, field->klass);
    }
    return 0;
}

int field_type(lua_State* L)
{
    auto field = luaL_checklightuserdata<UnityResolve::Field>(L, -2);
    if (field)
    {
        return luaL_pushlightuserdata<UnityResolve::Type>(L, field->type);
    }
    return 0;
}

int field_name(lua_State* L)
{
    auto field = luaL_checklightuserdata<UnityResolve::Field>(L, -2);
    if (field)
    {
        lua_pushstring(L, field->name.c_str());
        return 1;
    }
    return 0;
}
static const luaL_Reg field_fields[]
{
    {"name", field_name}, {"type", field_type}, {"class", field_class}, {"offset", field_offset}, {"static", field_static},{NULL, NULL}
};

/// @brief __index of method metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_field(lua_State *L)
{
    const char* key = lua_tostring(L, -1);
    auto ret = indexFields(L, field_fields, key);
    if (ret.second)
        return ret.first;
        
    return 0;
}

static const luaL_Reg field_m[]{
    {"__index", index_field}, {NULL, NULL}
};

/// @brief returns the name of a method as a string on the stack
/// @param L Lua State
/// @return 1 string on stack or 0
int name_method(lua_State *L)
{
    auto method = luaL_checklightuserdata<UnityResolve::Method>(L, -2);
    if (method != nullptr)
    {
        lua_pushstring(L, method->name.c_str());
        return 1;
    }
    else
    {
        return 0;
    }
}

int return_type_method(lua_State* L)
{
    auto method = luaL_checklightuserdata<UnityResolve::Method>(L, -2);
    if (method!= nullptr)
    {
        return luaL_pushlightuserdata<UnityResolve::Type>(L, method->return_type);
    }
    else {
        return 0;
    }
}
/*
local is = il2cpp.assemblies[1].classes[2]
print(is.methods[2].return_type.name)
*/
int args_method(lua_State* L)
{
    auto method = luaL_checklightuserdata<UnityResolve::Method>(L, -2);
    if (method != nullptr)
    {
        return vec2table<UnityResolve::Method::Arg>(L, method->args);
    }
    else {
        return 0;
    }
}
static const luaL_Reg method_fields[]{
    {"name", name_method}, {"return_type", return_type_method}, {"args", args_method}, {NULL, NULL}};

/// @brief __index of method metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_method(lua_State *L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, method_fields, key);
    if (ret.second)
        return ret.first;

    return 0;
}

static const luaL_Reg method_m[]{
    {"__index", index_method}, {NULL, NULL}};

/// @brief returns the methods of a class as a list on the stack
/// @param L Lua State
/// @return 1 table on the stack or 0
int methods_class(lua_State *L)
{
    auto cls = luaL_checklightuserdata<UnityResolve::Class>(L, -2);
    if (cls != nullptr)
        return vec2table<UnityResolve::Method>(L, cls->methods);
    else
        return 0;
}

/// @brief returns the name of the class on the stack
/// @param L Lua State
/// @return 1 string on the stack or 0
int name_class(lua_State *L)
{
    auto cls = luaL_checklightuserdata<UnityResolve::Class>(L, -2);
    if (cls != nullptr)
    {
        lua_pushstring(L, cls->name.c_str());
        return 1;
    }
    else
    {
        return 0;
    }
}

static const luaL_Reg class_fields[]{
    {"name", name_class}, {"methods", methods_class}, {NULL, NULL}
};

/// @brief __newindex of class metatable
/// @param L Lua State
/// @return number of elements on the stack
int newindex_class(lua_State *L)
{
    return 0;
}

/// @brief __index of class metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_class(lua_State *L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, class_fields, key);
    if (ret.second)
        return ret.first;
    return 0;
}

static const luaL_Reg class_m[] = {
    {"__index", index_class}, {"__newindex", newindex_class}, {NULL, NULL}
};

/// @brief returns the name of the assembly on the stack
/// @param L Lua State
/// @return 1 string on the stack or 0
int name_assembly(lua_State *L)
{
    auto assembly = luaL_checklightuserdata<UnityResolve::Assembly>(L, -2);
    if (assembly != nullptr)
    {
        lua_pushstring(L, assembly->name.c_str());
        return 1;
    }
    else
        return 0;
}

/// @brief returns the classes of an assembly as a list on the stack
/// @param L Lua State
/// @return 1 table on the stack or 0
int classes_assembly(lua_State *L)
{
    auto assembly = luaL_checklightuserdata<UnityResolve::Assembly>(L, -2);
    if (assembly != nullptr)
        return vec2table<UnityResolve::Class>(L, assembly->classes);
    else
        return 0;
}
static const luaL_Reg assembly_fields[] = {
        {"name", name_assembly}, {"classes", classes_assembly}, {NULL, NULL}
};

/// @brief __newindex of assembly metatable
/// @param L Lua State
/// @return number of elements on the stack
int newindex_assembly(lua_State *L)
{
    return 0;
}

/// @brief __index of assembly metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_assembly(lua_State *L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, assembly_fields, key);
    if (ret.second)
        return ret.first;

    return 0;
}

static const luaL_Reg assembly_m[]{
    {"__newindex", newindex_assembly}, {"__index", index_assembly}, {NULL, NULL}};

int assemblies_il2cpp(lua_State *L)
{
    return vec2table<UnityResolve::Assembly>(L, UnityResolve::assembly);
}

static const luaL_Reg il2cpp_fields[]{
    {"assemblies", assemblies_il2cpp}, {NULL, NULL}};

/// @brief __newindex of il2cpp metatable
/// @param L Lua State
/// @return number of elements on the stack
int newindex_il2cpp(lua_State *L)
{
    return 0;
}

/// @brief __index of il2cpp metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_il2cpp(lua_State *L)
{
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, il2cpp_fields, key);
    // a field was processed and maybe has returned something on the stack so
    if (ret.second)
        return ret.first;

    // this allows us to write a function called processFunctions, where we can check attemps to index a function

    // default case, no indexing, return nothing on the stack
    return 0;
}

static const luaL_Reg il2cpp_m[] =
{
    {"__newindex", newindex_il2cpp}, {"__index", index_il2cpp}, {NULL, NULL}
};

/// @brief Registers il2cpp library in lua
/// @param L Lua State
/// @return 0
int lua_bindings::register_il2cpp_bridge(lua_State *L)
{
    create_lua_mt(L, ASSEMBLY_MT_NAME, assembly_m);
    create_lua_mt(L, CLASS_MT_NAME, class_m);
    create_lua_mt(L, FIELD_MT_NAME, field_m);
    create_lua_mt(L, METHOD_MT_NAME, method_m);
    create_lua_mt(L, TYPE_MT_NAME, type_m);
    create_lua_mt(L, ARG_MT_NAME, arg_m);
    create_lua_mt(L, IL2CPP_MT_NAME, il2cpp_m);
    register_global_table_with_mt(L, "il2cpp", IL2CPP_MT_NAME);
    bindMt();
    return 0;
}