
function raytracer_project(_name, _kind, _defines)

   project ("raytracer" .. _name)
      kind (_kind)

      includedirs {
         RAYTRACER_DIR .. "_source/_engine",
      }

      defines {
         _defines,
      }

      links {
      }

      configuration { "debug or development" }
         flags {
            "Symbols"
         }
         defines {
            "_DEBUG",
         }

      configuration { "release" }
         defines {
            "NDEBUG"
      }

      configuration { "vs*" }
         links {
            "dbghelp"
      }

      configuration {}

      files {
         RAYTRACER_DIR .. "_source/_engine/**.h",
         RAYTRACER_DIR .. "_source/_engine/**.cpp",
         RAYTRACER_DIR .. "_source/_engine/*/**.h",
         RAYTRACER_DIR .. "_source/_engine/*/**.cpp",
         RAYTRACER_DIR .. "_source/_client/**.h",
         RAYTRACER_DIR .. "_source/_client/**.cpp",
         RAYTRACER_DIR .. "_source/_client/*/**.h",
         RAYTRACER_DIR .. "_source/_client/*/**.cpp"
      }

		strip()

		configuration {} -- reset configuration
end
