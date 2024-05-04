#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <luau/VM/include/lua.h>
#include <luau/VM/include/lualib.h>
#include <HookManager/include/HookManager.hpp>
#include "ui/ui.hpp"
#include "globals/globals.hpp"
#include "utils/singleton.hpp"
#include "utils/progress_manager.hpp"
#include "utils/console/console.hpp"
#include <texteditor/TextEditor.h>
#include <UnityResolve/UnityResolve.hpp>
#include "Lua/LuaVM.hpp"
using H = HookManager;


ProgressManager m_InitProgress(5);
DWORD WINAPI MainThread()
{
    
    Console::get()->open();
    m_InitProgress.Step("Created console !");
    LuaVM::get()->InitVM();
    m_InitProgress.Step("Started Luau VM");
    ui::RegisterWidgets();
    m_InitProgress.Step("Registered Widgets");
    ui::HookDX11();
    m_InitProgress.Step("Created DX HOOK");
    UnityResolve::Init(GetModuleHandleW(L"GameAssembly.dll"), UnityResolve::Mode::Il2Cpp);
    m_InitProgress.Step("Initiated UnityResolve.hpp");
    Console::get()->log("IL2CppLuau Started !");
    std::cin.ignore();
    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,    // handle to DLL module
    DWORD fdwReason,    // reason for calling function
    LPVOID lpvReserved) // reserved
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        GlobalsManager::get()->HModule() = hModule;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr); // Start the main thread
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE; // Successful DLL_PROCESS_ATTACH.
}
