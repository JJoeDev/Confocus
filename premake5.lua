workspace "Confocus"
  configurations { "Debug", "Release" }
  location "build"

  filter "configurations:Debug"
    defines {
      "DEBUG"
    }
    optimize "Debug"
    symbols "On"

  filter "configurations:Release"
    defines {
      "NDEBUG"
    }
    optimize "On"

project "Confocus"
  kind "ConsoleApp"
  language "C++"
  targetdir ("bin/%{cfg.buildcfg}")
  objdir ("bin/%{cfg.buildcfg}")

  files {
    "src/**.cpp",
    "src/**.h"
  }

  includedirs{
    
  }
