#ifndef EXECUTOR_WIDGET_HPP
#define EXECUTOR_WIDGET_HPP
#include "../ui.hpp"
#include "../../utils/console/console.hpp"

#include <texteditor/TextEditor.h>
#include "../../lua/LuaVM.hpp"
#include <string>
class ExecutorWidget : public Widget, public Singleton<ExecutorWidget>
{
    TextEditor editor;
    public:
    ExecutorWidget() { setName("ExecutorWidget");}
    void Init() override
    {
        Console::get()->log("Starting editor widget");
        editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
    }
    void Render() override
    {
        if (ImGui::Begin("Editor"))
        {
            ImGui::Text(this->getName().c_str());
            if (ImGui::Button("execute"))
            {
                auto str = LuaVM::get()->executeScript(editor.GetText());
                if (str != "")
                    Console::get()->error(str);
            }
            if (ImGui::Button("auto complete"))
            {
                lua_State* L = LuaVM::get()->LuaState();
                lua_getglobal(L, "_G");
                int tbl = lua_gettop(L);
                /* table is in the stack at index 't' */
                lua_pushnil(L);  /* first key */
                while (lua_next(L, t) != 0) {
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                printf("%s - %s\n",
                        lua_typename(L, lua_type(L, -2)),
                        lua_typename(L, lua_type(L, -1)));
                /* removes 'value'; keeps 'key' for next iteration */
                lua_pop(L, 1);
            }
            }
            editor.Render("Executor");
            ImGui::End();
        }
    }

    TextEditor& GetEditor()
    {
        return editor;
    }
};

#endif