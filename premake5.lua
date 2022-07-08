workspace "Chess"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Chess"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    includedirs { "dependencies/SFML-2.5.1/include" }
    libdirs { "dependencies/SFML-2.5.1/lib" }

    files { "src/**.hpp", "src/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        links { "sfml-graphics-d", "sfml-system-d", "sfml-window-d" }
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        links { "sfml-graphics", "sfml-system", "sfml-window" }
    
    filter "system:Windows"
        cppdialect "C++17"
        defines { "WINDOWS" }
    
    filter { "configurations:Debug", "system:Windows" }
        postbuildcommands {
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-graphics-d-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\""),
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-system-d-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\""),
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-window-d-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\"")
        }
    
    filter { "configurations:Release", "system:Windows" }
        postbuildcommands {
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-graphics-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\""),
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-system-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\""),
            ("copy \"dependencies\\SFML-2.5.1\\bin\\sfml-window-2.dll\" \"bin/" .. outputdir .. "/%{prj.name}\"")
        }