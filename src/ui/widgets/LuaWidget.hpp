#ifndef LUA_WIDGET_HPP
#define LUA_WIDGET_HPP
#include "../widget.hpp"
#include <lua.h>
#include <lualib.h>
#include <luacode.h>
#include "../../Lua/LuaVM.hpp"
#include "../../Lua/LuaClosure.hpp"

class LuaWidget : public Widget
{
    public:
    LuaWidget(const char* name = "LuaWidget") {setName(name);}
    
    void Init() override
    {
        init_lua.CallFunc(LuaVM::get()->LuaState());
    }

    void Render() override
    {
        render_lua.CallFunc(LuaVM::get()->LuaState());
    }

    void SetInit(LuaClosure func)
    {
        init_lua = func;
    }

    void SetRender(LuaClosure func)
    {
        render_lua = func;
    }

    private:
    LuaClosure init_lua;
    LuaClosure render_lua;
};

#endif