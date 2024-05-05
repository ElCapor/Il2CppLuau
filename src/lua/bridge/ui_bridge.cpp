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
    LuaClosure init_func;
    LuaClosure render_func;
    
    if (lua_istable(L, -1))
    {
        printf("is a table\n");

        // Get the 'name' field
        lua_getfield(L, -1, "name");
        if (lua_isstring(L, -1))
        {
            printf("name\n");
            widget_name = lua_tostring(L, -1);
        } else{
            printf("name field is not a string\n");
            lua_pop(L, 1);
            return 0;
        }
        lua_pop(L, 1);

        // Get the 'init' field
        lua_getfield(L, -1, "init");
        if (lua_isfunction(L, -1))
        {
            printf("init\n");
            init_func.ref = lua_ref(L, -1);
        } else {
            printf("init field is not a function\n");
            lua_pop(L, 1);
            return 0;
        }
        lua_pop(L, 1);

        // Get the 'render' field
        lua_getfield(L, -1, "render");
        if (lua_isfunction(L, -1))
        {
            printf("render\n");
            render_func.ref = lua_ref(L, -1);
        } else {
            printf("render field is not a function\n");
            lua_pop(L, 1);
            return 0;
        }
        lua_pop(L, 1);

        // Create and return the widget
        LuaWidget* widget = new LuaWidget(widget_name);
        widget->SetInit(init_func);
        widget->SetRender(render_func);
        lua_pushlightuserdata(L, widget);
        luaL_getmetatable(L, WIDGET_MT);
        lua_setmetatable(L, -2);
        return 1;
    }
    printf("not a table\n");
    return 0;
}

int widget_register(lua_State* L)
{
    auto widget = luaL_checklightuserdata<LuaWidget>(L, -1);
    if (widget != nullptr)
    {
        ui::RegisterWidget(widget);
        return 0;
    }else {
        return 0;
    }
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
    return vec2table<Widget>(L, ui::m_Widgets.getCurrentBuffer());
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
    lua_getglobal(L, "ui");
    lua_pushcfunction(L, widget_new, "new");
    lua_setfield(L, -2, "new_widget");
    lua_pushcfunction(L, widget_register, "register");
    lua_setfield(L, -2, "register_widget");
    lua_pop(L, -1);
    return 0;
}