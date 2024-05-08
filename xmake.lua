
add_rules("mode.debug", "mode.release")

package("luau")

    set_homepage("https://luau-lang.org/")
    set_description("A fast, small, safe, gradually typed embeddable scripting language derived from Lua.")
    set_license("MIT")
    set_sourcedir(path.join(os.scriptdir(), "extern/vendor/luau"))

    add_configs("extern_c", { description = "Use extern C for all APIs.", default = false, type = "boolean" })
    add_configs("build_web", { description = "Build web module.", default = false, type = "boolean" })

    add_deps("cmake")

    on_install("linux", "windows", "mingw|x86_64", "macosx", function(package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "RelWithDebInfo"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        table.insert(configs, "-DLUAU_BUILD_TESTS=OFF")
        table.insert(configs, "-DLUAU_BUILD_WEB=" .. (package:config("build_web") and "ON" or "OFF"))
        table.insert(configs, "-DLUAU_EXTERN_C=" .. (package:config("extern_c") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs, { buildir = "build" })
        -- need to link with Ast last
        local libs = { "Luau.VM", "Luau.Compiler", "Luau.Ast" }
        for _, link in ipairs(libs) do
            package:add("links", link)
        end
    end)
package_end()


add_requires("luau")

target("Il2CppLuau")
    set_kind("shared")
    set_languages("cxx20")
    add_files("src/**.cpp")
    add_files("extern/vendor/imgui/imgui_demo.cpp","extern/vendor/imgui/imgui_draw.cpp", "extern/vendor/imgui/imgui_tables.cpp", "extern/vendor/imgui/imgui_widgets.cpp", "extern/vendor/imgui/imgui.cpp")
    add_includedirs("extern/vendor/imgui")
    add_files("extern/vendor/imgui/backends/imgui_impl_win32.cpp", "extern/vendor/imgui/backends/imgui_impl_dx11.cpp")
    add_headerfiles("extern/vendor/imgui/backends/imgui_impl_win32.h")
    add_files("extern/vendor/texteditor/TextEditor.cpp","extern/vendor/texteditor/LanguageDefinitions.cpp")
    add_files("extern/vendor/kiero/**.cpp")
    add_includedirs("extern/vendor")
    add_includedirs("extern/include")
    add_links("extern/vendor/HookManager/lib/detours", "user32")
    add_includedirs("extern/vendor/luau/VM/include")
    add_includedirs("extern/vendor/luau/Compiler/include", "extern/vendor/luau/Common/include", "extern/vendor/luau/Ast/include")
    add_packages("luau")
    -- TODO : Add source dir from package
target_end()

target("injector")
    set_kind("binary")
    set_languages("cxx20")
    add_files("injector/**.cpp")
    add_links("user32", "winmm", "comdlg32", "ole32")
target_end()