#ifndef LUAVM_HPP
#define LUAVM_HPP

#include <string>
#include <memory>
#include <map>

#include "../utils/singleton.hpp"

#include <luau/VM/include/lua.h>
#include <luau/VM/include/lualib.h>
#include <luau/VM/src/lfunc.h>
#include <luau/Compiler/include/luacode.h>
#include <luau/Common/include/Luau/Common.h>
struct LuaVMOptions {
    bool debug = false;
    bool register_functions = true;
    bool emulate_roblox = false;
    bool sandbox_libs = true; // sandbox libraries and env
    std::string vname = "main"; // virtual script name

    lua_CompileOptions* compile_options = new lua_CompileOptions();
};



class LuaVM : public Singleton<LuaVM>
{
    LuaVMOptions options;
    public:
        LuaVM();
        ~LuaVM();

        void setOptions(const LuaVMOptions& options);
        LuaVMOptions& getOptions();
        void SetupState(lua_State* L);
        void RegisterFunctions(lua_State* L);
        std::string runCode(lua_State* L, const std::string& code);
        std::string executeScript(std::string script);
};


#endif