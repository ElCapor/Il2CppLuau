#include "lextra.h"

/// @brief Creates a new lua metatable based on the provided functions
/// @param L Lua State
/// @param mt_name name of the metatable
/// @param m_reg array of functions
void create_lua_mt(lua_State *L, const char *mt_name, const luaL_Reg *m_reg)
{
    luaL_newmetatable(L, mt_name);

    for (const luaL_Reg *method = m_reg; method->name != NULL; method++)
    {
        lua_pushstring(L, method->name);
        lua_pushcfunction(L, method->func, method->name);
        lua_settable(L, -3);
    }
}
/// @brief registers a global table with a given metatable
/// @param L Lua State
/// @param table_name the global name of the table
/// @param mt_name the metatable of the table
void register_global_table_with_mt(lua_State *L, const char *table_name, const char *mt_name)
{
    lua_newtable(L);
    luaL_getmetatable(L, mt_name);
    lua_setmetatable(L, -2);
    lua_setglobal(L, table_name);
}