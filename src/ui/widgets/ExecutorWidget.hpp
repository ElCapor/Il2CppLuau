#ifndef EXECUTOR_WIDGET_HPP
#define EXECUTOR_WIDGET_HPP
#include "../ui.hpp"
#include "../../utils/console/console.hpp"

#include <texteditor/TextEditor.h>
#include "../../lua/LuaVM.hpp"
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