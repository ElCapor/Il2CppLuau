#ifndef LUA_WIDGET_HPP
#define LUA_WIDGET_HPP
#include "../ui.hpp"
#include <lua.h>
#include <lualib.h>
#include <luacode.h>
#include "../../Lua/LuaVM.hpp"

class LuaWidget : public Widget
{
    public:
    LuaWidget(const char* name = "LuaWidget") {setName(name);}
    
    void Init() override
    {
        init_lua(LuaVM::get()->LuaState());
    }

    void Render() override
    {
        render_lua(LuaVM::get()->LuaState());
    }

    void SetInit(lua_CFunction func)
    {
        init_lua = func;
    }

    void SetRender(lua_CFunction func)
    {
        render_lua = func;
    }

    private:
    lua_CFunction init_lua;
    lua_CFunction render_lua;
};

#endif