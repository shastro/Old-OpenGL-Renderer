-- premake5.lua

workspace "cse389"
   configurations { "Default", "UseLua" }

project "museum"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin"
   includedirs {"include", "/usr/include/glm", "/usr/include/lua5.3", "usr/include/assimp"}
   libdirs {os.findlib("lua")}
   links {"lua5.3", "GL", "GLEW", "glfw", "scriptloaderLib", "primitivesLib", "stdc++fs", "assimp"}
   buildoptions {"-std=c++17", "-Wall", "-ggdb", "-lstdc++fs" , "-lassimp"}

   files { "src/main.cpp" }

   filter "configurations:UseLua"
      defines { "USING_LUA"}

project "scriptloaderLib"
   kind "StaticLib"
   language "C++"
   targetdir "build"
   includedirs {"include", "/usr/include/glm", "/usr/include/lua5.3"}

   files "src/scriptloader/*.cpp"

   filter "configurations:UseLua"
      defines { "USING_LUA" }

project "primitivesLib"
   kind "StaticLib"
   language "C++"
   targetdir "build"
   includedirs {"include", "/usr/include/glm", "/usr/include/lua5.3", "usr/include/assimp"}
   links {"lua5.3", "GL", "GLEW", "glfw"}
   buildoptions {"-std=c++17", "-Wall", "-g3", "-lstdc++fs", "-lassimp"}
   files "src/primitives/*.cpp"
    defines { "STB_IMAGE_IMPLEMENTATION"}
