
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

package("HookManager")
    set_sourcedir(path.join(os.scriptdir(), "extern/vendor/HookManager"))
    add_includedirs("extern/vendor/HookManager/include")
    on_install("windows", function(package) 
        package:add("links", "detours")
    end)
package_end()

add_requires("luau")
add_requires("HookManager")

target("Il2CppLuau")
    set_kind("shared")
    set_languages("cxx20")
    add_files("src/*.cpp")
    add_includedirs("extern/vendor")
    add_includedirs("extern/include")
    add_packages("luau")
    -- TODO : Add source dir from package
    add_packages("HookManager")
