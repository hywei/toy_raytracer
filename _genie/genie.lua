
RAYTRACER_DIR = (path.getabsolute("..") .. "/")
local RAYTRACER_BUILD_DIR = (RAYTRACER_DIR .. "_build/")

solution "raytracer"
    configurations {
        "debug",
        "development",
        "release",
    }

    platforms {
        "x32",
        "x64",
        "native"
    }

    language "C++"

    configuration {}

dofile ("toolchain.lua")
dofile ("raytracer.lua")

toolchain(RAYTRACER_BUILD_DIR, "")


group "raytracer"
raytracer_project("", "ConsoleApp", {})


-- Install
configuration { "x32", "vs*" }
    postbuildcommands {
        --"cp -r " .. RAYTRACER_DIR .. "_build/win32/bin/* " .. "$(MONSTER_INSTALL_DIR)/" .. "bin/win32/",
    }

configuration { "x64", "vs*" }
    postbuildcommands {
        --"cp -r " .. RAYTRACER_DIR .. "_build/win64/bin/* " .. "$(MONSTER_INSTALL_DIR)/" .. "bin/win64/",
    }
