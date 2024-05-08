#include <stdio.h>
#include <Windows.h>
#include "sandbox/app.hpp"
#include "ui/widgets/ExecutorWidget.hpp"
#include "Lua/LuaVM.hpp"


#include <luau/VM/src/lobject.h>
#include <luau/VM/src/lapi.h>
#include <luau/VM/src/lstate.h>
#include <algorithm>
template<typename T>
static T read(uint8_t* data, size_t& offset)
{

    T result;
    memcpy(&result, data + offset, sizeof(T));
    offset += sizeof(T);

    return result;
}

static uint32_t readVarInt(uint8_t* data, size_t& offset)
{
    uint32_t result = 0;
    uint32_t shift = 0;

    uint8_t byte;

    do
    {
        byte = read<uint8_t>(data, offset);
        result |= (byte & 127) << shift;
        shift += 7;
    } while (byte & 128);

    return result;
}


int proto_inspector(lua_State* L)
{
    if (lua_isLfunction(L, -1))
    {
        const TValue* func = luaA_toobject(L, -1);
        Proto* proto = clvalue(func)->l.p;
        uint8_t* data = proto->typeinfo;
        if (data != nullptr)
        {
            size_t offset = 0;

            uint32_t typeSize = readVarInt(data, offset);
            uint32_t upvalCount = readVarInt(data, offset);
            uint32_t localCount = readVarInt(data, offset);

            Console::get()->log("Proto ", typeSize, " upval ", upvalCount, " locals ", localCount);
            std::vector<uint8_t> argumentTypes;
            uint8_t* types = (uint8_t*)data + offset;

            argumentTypes.resize(proto->numparams);

            // Skip two bytes of function type introduction
            memcpy(argumentTypes.data(), types + 2, proto->numparams);
            offset += typeSize;
            for (auto& tp : argumentTypes)
            {
                Console::get()->log("tp : ", tp);
            }



        }
        
    }
    return 0;
}


/*
local f = function(var :int) :int
return 100
end
proto_inspector(f)*/
// Main code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Console::get()->open();
    LuaVM::get()->InitVM();
    lua_State* L = LuaVM::get()->LuaState();
    lua_pushcfunction(L, proto_inspector, "proto_inspector");
    lua_setglobal(L, "proto_inspector");
    App::get()->GetGuiManager().AddWidget(new ExecutorWidget());
    App::get()->Run();
    return 0;
}
