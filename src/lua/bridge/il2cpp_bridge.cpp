#include "il2cpp_bridge.h"
#include "lualib.h"
#include "lua.h"
#include "../../utils/console/console.hpp"
#include <UnityResolve/UnityResolve.hpp>
#include "../lextra.h"

#define ASSEMBLY_MT_NAME "assembly.mt"
#define IL2CPP_MT_NAME "il2cpp.mt"
#define CLASS_MT_NAME "class.mt"
#define FIELD_MT_NAME "field.mt"
#define METHOD_MT_NAME "method.mt"

/// @brief Creates a table on the stack with all the content of a vector of type T* like a list
/// @tparam T type of the vector
/// @param L Lua State
/// @param vec The std::vector
/// @return 1 if success (table on the stack) else 0
template <typename T>
int vec2table(lua_State *L, std::vector<T *> vec)
{
    // better return nil if table is empty, allows to perform bool checks
    if (vec.size() > 0)
    {
        int idx = 1; // lua indexes start at 1
        lua_newtable(L);
        for (auto &pObj : vec)
        {
            lua_pushlightuserdata(L, pObj);
            if constexpr (std::is_same_v<T, UnityResolve::Assembly>)
                luaL_getmetatable(L, ASSEMBLY_MT_NAME);
            else if constexpr (std::is_same_v<T, UnityResolve::Class>)
                luaL_getmetatable(L, CLASS_MT_NAME);
            else if constexpr (std::is_same_v<T, UnityResolve::Method>)
                luaL_getmetatable(L, METHOD_MT_NAME);
            else if constexpr (std::is_same_v<T, UnityResolve::Field>)
                luaL_getmetatable(L, FIELD_MT_NAME);
            else
            {
                Console::get()->error("Can't convert type ", typeid(T).name(), " to table");
                return 0;
            }
            lua_setmetatable(L, -2);
            lua_rawseti(L, -2, idx);
            idx++;
        }
        return 1;
    }
    return 0;
}

/// @brief index fields for a metatable based on predefined fields along their functions
/// @param L Lua State
/// @param fields the luaL_Reg* array containing the field names and associated functions
/// @return (int,bool) where int is the number of items on the stack , and bool tells if any field was processed
std::pair<int, bool> indexFields(lua_State *L, const luaL_Reg *fields)
{
    const char *key = luaL_checkstring(L, -1);
    for (const luaL_Reg *field = fields; field->name != NULL; field++)
    {
        if (strcmp(key, field->name) == 0)
        {
            return std::make_pair<int, bool>(field->func(L), true); // field was processed
        }
    }
    return std::make_pair<int, bool>(0, false); // no fields were processed
}

/// @brief __index of method metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_field(lua_State *L)
{
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

static const luaL_Reg method_fields[]{
    {"name", name_method}, {NULL, NULL}};

/// @brief __index of method metatable
/// @param L Lua State
/// @return number of elements on the stack
int index_method(lua_State *L)
{
    auto ret = indexFields(L, method_fields);
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
    auto ret = indexFields(L, class_fields);
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
    auto ret = indexFields(L, assembly_fields);
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
    auto ret = indexFields(L, il2cpp_fields);
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
    create_lua_mt(L, IL2CPP_MT_NAME, il2cpp_m);
    register_global_table_with_mt(L, "il2cpp", IL2CPP_MT_NAME);
    return 0;
}