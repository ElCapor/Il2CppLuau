#ifndef CONTAINER_BRIDGE_HPP
#define CONTAINER_BRIDGE_HPP
#include "lua.h"


namespace lua_bindings
{
    int register_ccontainer_bridge(lua_State* L);
}

#endif