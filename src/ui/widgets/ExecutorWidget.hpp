#ifndef EXECUTOR_WIDGET_HPP
#define EXECUTOR_WIDGET_HPP
#include "../ui.hpp"
#include "../../utils/console/console.hpp"

#include <texteditor/TextEditor.h>
class ExecutorWidget : public Widget, public Singleton<ExecutorWidget>
{
    TextEditor editor;
    public:
    void Init() override
    {
        Console::get()->log("Starting editor widget");
        editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
    }
    void Render() override
    {
        ImGui::ShowDemoWindow();
        if (ImGui::Begin("Editor"))
        {
            if (ImGui::Button("execute"))
            {
                Console::get()->log("kys");
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