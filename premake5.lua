workspace "Liff_of_a_pi"
	configurations {"Debug", "Release"}
	startproject "TestProject"
	
	flags {"MultiProcessorCompile"}
	
	filter "configurations:Debug"
		defines{"Debug"}
		symbols "on"
		
	filter "configurations:Release"
		defines{"Release"}
		optimize "Speed"
		flags {"LinkTimeOptimization"}

	group "External"
		include "external/glad.lua"
		include "external/glfw.lua"
		include "external/glm.lua"
		include "external/imgui.lua"
	group ""
		
	
	project "DemoProject"
		location "DemoProject"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		architecture "x86_64"
		
		targetdir "bin/%{cfg.buildcfg}/"
		objdir "bin-int/%{cfg.buildcfg}/"
		
		includedirs
		{
			"DemoProject/include/",
			"external/glad/include",
			"external/glfw/include",
			"external/glm/",
			"external/imgui/",
			"external/imgui/examples/"
		}
		
		files{"DemoProject/src/**.cpp", "DemoProject/src/**.h"}
		links {"GLFW", "GLM", "GLAD", "ImGui"}
		
		filter "system:windows"
			defines{"_WINDOWS"}
			systemversion "latest"
			staticruntime "On"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
		filter "configurations:Release"
			runtime "Release"
			optimize "on"


	project "Liff"
		location "Liff"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		architecture "x86_64"
	
		targetdir "bin/%{cfg.buildcfg}"
		objdir "bin-int/%{cfg.buildcfg}"

		pchheader "liffpch.h"
		pchsource "Liff/src/liffpch.cpp"
	
		files 
		{ 		
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs 
		{
			"%{prj.name}/src/",
			"external/glad/include",
			"external/glfw/include",
			"external/glm/",
			"external/imgui/",
			"external/imgui/examples/"
		}

		links {"GLFW", "GLM", "GLAD", "ImGui"}
	
		filter "system:windows"
			systemversion "latest"
			staticruntime "On"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
		filter "configurations:Release"
			runtime "Release"
			optimize "on"


	project "TestProject"
		location "TestProject"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		architecture "x86_64"
		
		targetdir "bin/%{cfg.buildcfg}/"
		objdir "bin-int/%{cfg.buildcfg}/"
		
		includedirs
		{
			"Liff/src",
			"TestProject/include/",
			"external/glad/include",
			"external/glfw/include",
			"external/glm/",
			"external/imgui/",
			"external/imgui/examples/"
		}
		
		files{"TestProject/src/**.cpp", "TestProject/src/**.h"}
		links {"GLFW", "GLM", "GLAD", "ImGui", "Liff"}
		
		filter "system:windows"
			defines{"_WINDOWS"}
			systemversion "latest"
			staticruntime "On"

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
		filter "configurations:Release"
			runtime "Release"
			optimize "on"
