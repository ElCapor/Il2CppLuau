#ifndef EXECUTOR_WIDGET_HPP
#define EXECUTOR_WIDGET_HPP
#include "../ui.hpp"
#include "../../utils/console/console.hpp"

#include <texteditor/TextEditor.h>
#include "../../lua/LuaVM.hpp"

std::vector<std::string> cacheGlobals();
std::vector<std::string> matches(std::string prefix);
class ExecutorWidget : public Widget, public Singleton<ExecutorWidget>
{
    TextEditor editor;

public:
    ExecutorWidget() { setName("ExecutorWidget"); }
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
            if (ImGui::Button("Autocomplete"))
            {
                for (auto& match : matches(editor.GetText()))
                {
                    Console::get()->log(match);
                }
            }
            editor.Render("Executor");
            ImGui::End();
        }
    }

    TextEditor &GetEditor()
    {
        return editor;
    }
};

#endif