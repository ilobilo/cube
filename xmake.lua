add_rules("mode.release")
add_rules("plugin.compile_commands.autoupdate", { outputdir = "$(buildir)" })

add_requires("glm")
add_requires("ncursesw")

target("cube")
    set_kind("binary")
    add_packages("glm", "ncursesw")

    add_files("src/main.cpp", "src/cube.cpp")
    add_includedirs("src/")

    set_languages("c++20")
    set_warnings("all", "error")
    set_optimize("fastest")