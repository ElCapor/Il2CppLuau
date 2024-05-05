/***
 * Bridge to create ui components from lua
*/
#include "ui_bridge.h"
#include "../lextra.h"
#include "../../ui/widgets/LuaWidget.hpp"
#include "../mt_map.h"
#include <new>
#define WIDGET_MT "widget.mt"
#define UI_MT "ui.mt"




void bindUiMt()
{
    INSERT_MT(Widget, WIDGET_MT);
    metatableMap()["ui"] = UI_MT;
}

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

int widget_new(lua_State* L)
{
    const char* widget_name;
    lua_CFunction init_func;
    lua_CFunction render_func;
    
    if (lua_istable(L, -2))
    {
        if (lua_getfield(L, -2, "name") == LUA_TSTRING)
        {
            widget_name = lua_tostring(L, -1);
        } else{
            lua_pop(L, -1);
            return 0;
        }
        if (lua_getfield(L, -2, "init") == LUA_TFUNCTION)
        {
            init_func = lua_tocfunction(L, -1);
        } else {
            lua_pop(L, -1);
            return 0;
        }
        if (lua_getfield(L, -2, "render") == LUA_TFUNCTION)
        {
            render_func = lua_tocfunction(L, -1);
        } else {
            lua_pop(L, -1);
            return 0;
        }
        LuaWidget* widget = new LuaWidget(widget_name);
        lua_pushlightuserdata(L, widget);
        luaL_getmetatable(L, WIDGET_MT);
        lua_setmetatable(L, -2);
        return 1;
    }
    return 0;
}
static const luaL_Reg widget_funcs[]
{
    {"new", widget_new},{NULL, NULL}
};

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
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, widget_fields, key);
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
    const char* key = luaL_checkstring(L, -1);
    auto ret = indexFields(L, ui_fields, key);
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