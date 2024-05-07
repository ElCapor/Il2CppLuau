#include "ExecutorWidget.hpp"

std::vector<std::string> cacheGlobals()
{
    std::vector<std::string> globals;
    /* table is in the stack at index 't' */
    lua_State *L = LuaVM::get()->LuaState();
    lua_getglobal(L, "_G");
    int tbl = lua_gettop(L);
    lua_pushnil(L); /* first key */
    while (lua_next(L, tbl) != 0)
    {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        lua_pushvalue(L, -2); /* duplicate key */
        const char* key = lua_tostring(L, -1);
        globals.push_back(key);
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 2);
    }
    return globals;
}

std::vector<std::string> matches(std::string prefix) {
    std::vector<std::string> filtered;
    auto globals = cacheGlobals();
    for (const auto &s : globals) {
        if (s.find(prefix) == 0) {
        filtered.push_back(s);
        }
    }
    return filtered;
}