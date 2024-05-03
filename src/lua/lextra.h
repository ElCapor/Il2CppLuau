#ifndef LEXTRA_HPP
#define LEXTRA_HPP
#include <lua.h>
#include <lualib.h>
#include <luacode.h>
#include <utility>
#include <vector>
#include "mt_map.h"
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

std::pair<int, bool> indexFields(lua_State *L, const luaL_Reg *fields);

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
            auto mt = getMetatable<T>();
            if (mt != "")
            {
                luaL_getmetatable(L, mt.c_str());
            }
            else
            {
                printf("[ERROR] Can't convert type %s to a table", typeid(T).name());
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

#endif