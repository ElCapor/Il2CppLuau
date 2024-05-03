#ifndef LEXTRA_HPP
#define LEXTRA_HPP
#include <lua.h>
#include <lualib.h>
#include <luacode.h>
/***
 * Extra functions to help doing lua operations
*/

/// @brief Checks if there is a lightuserdata at the specified index
/// @tparam T type of the lightuserdata to return
/// @param L Lua State
/// @param idx index of the userdata
/// @return a pointer to an object or else nullptr
template <typename T>
T *luaL_checklightuserdata(lua_State *L, int idx)
{
    if (lua_isuserdata(L, idx))
    {
        void *ptr = lua_tolightuserdata(L, idx);
        if (ptr != nullptr)
        {
            return static_cast<T *>(ptr);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

void create_lua_mt(lua_State *L, const char *mt_name, const luaL_Reg *m_reg);

void register_global_table_with_mt(lua_State *L, const char *table_name, const char *mt_name);

#endif