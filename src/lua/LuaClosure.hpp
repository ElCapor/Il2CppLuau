#ifndef LUACLOSURE_HPP
#define LUACLOSURE_HPP
/*
*  Taken from my project here https://github.com/ElCapor/Event-System/blob/main/src/LuaVM/LuaClosure.hpp
* NOTE : should i use event systems in this app ?
* */
#include <lua.h>
#include <luacode.h>
#include <lualib.h>

using LuaClosureID = int;

// abstract class to represent a lua closure
class LuaClosure
{
public:
    static LuaClosureID maxID; // maxID used
    LuaClosureID id;           // id of current closure
    int ref; // reference to the colsure in the lua registery

    LuaClosure()
    {
        maxID++;
        id = maxID;
    }
    // a closure only makes sense inside a lua state
    void CallFunc(lua_State* L)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        luaL_checktype(L, -1, LUA_TFUNCTION); // Just to be sure
        lua_call(L, 0, 0);
    }

    void Delete(lua_State* L)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
        luaL_checktype(L, -1, LUA_TFUNCTION); // Just to be sure
        lua_unref(L, ref); // assuming you're done with it
    }
};
#endif