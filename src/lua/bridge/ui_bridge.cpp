/***
 * Bridge to create ui components from lua
*/
#include "ui_bridge.h"
#include "../lextra.h"
#include "../../ui/ui.hpp"
#include "../mt_map.h"

#define WIDGET_MT "widget.mt"
#define UI_MT "ui.mt"


/* Representation of a widget as a lua table
* local widget = {
    "init" = function()
        -- init any field here
    end

    "render" = function()
        imgui.text("Hello world !")
        -- imgui is going to be a local table with an index mt
    end

    "name" = "LuaWidget"
}
* 
* */

void bindUiMt()
{
    INSERT_MT(Widget, WIDGET_MT);
    metatableMap()["ui"] = UI_MT;
}

int widget_name(lua_State* L)
{
    auto widget = luaL_checklightuserdata<Widget>(L, -2);
    if (widget != nullptr)
    {
        lua_pushstring(L, widget->getName().c_str());
        return 1;
    } else {
        return 0;
    }
}

int widget_id(lua_State* L)
{
    auto widget = luaL_checklightuserdata<Widget>(L, -2);
    if (widget != nullptr)
    {
        lua_pushinteger(L, widget->getId());
        return 1;
    } else {
        return 0;
    }
}

static const luaL_Reg widget_fields[]
{
    {"name", widget_name}, {"id", widget_id},{NULL, NULL}
};

int widget_index(lua_State* L)
{
    auto ret = indexFields(L, widget_fields);
    if (ret.second)
        return ret.first;
    return 0;
}

static const luaL_Reg widget_m[]
{
    {"__index", widget_index},{NULL, NULL}
};

int widgets_ui(lua_State* L)
{
    return vec2table<Widget>(L, ui::m_Widgets);
}

static const luaL_Reg ui_fields[] =
{
    {"widgets", widgets_ui},{NULL, NULL}
};

int ui_index(lua_State* L)
{
    auto ret = indexFields(L, ui_fields);
    if (ret.second)
        return ret.first;
    return 0;
}

static const luaL_Reg ui_m[]
{
   {"__index", ui_index} ,{NULL, NULL}
};

int lua_bindings::register_ui_bridge(lua_State* L)
{
    bindUiMt();
    create_lua_mt(L, WIDGET_MT, widget_m);
    create_lua_mt(L, UI_MT, ui_m);
    register_global_table_with_mt(L, "ui", UI_MT);
    return 0;
}