## CSE 389 Project

Elias Flores, Skyler Hughes, Wesly Pick-Roth

----------------------------------------------

### Dependencies
*  Premake5 (to generate makefile) https://premake.github.io/download.html
*  OpenGl
*  glfw
*  Lua (optional)
*  Assimp

### Build instructions
To generate gnu makefile:
```
premake5 gmake
```
To build (with -j# to multithread compilation):
```
make -j3
```
To run:
```
./bin/museum
```
