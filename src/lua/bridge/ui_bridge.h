#ifndef ui_bridge_hpp
#define ui_bridge_hpp
#include <lua.h>

namespace lua_bindings
{
    int register_ui_bridge(lua_State* L);
}

#endif