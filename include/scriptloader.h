#ifndef SCRIPTLOADER_H
#define SCRIPTLOADER_H

#ifdef USING_LUA

// Include the Lua library
// In order to link correctly, must let the compiler know
// it's a C library
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <vector>
#include <iostream>

class ScriptLoaderError {
private:
	std::string err;
public:
	ScriptLoaderError(std::string err);
	void printError();
};

class ScriptLoader {
protected:
	lua_State *L;

	// Get a global variable
	template <class T>
	T get_var(std::string name);

	// Get field from a table
	template <class T>
	T get_field(std::string table, std::string field);
public:
	ScriptLoader(std::string scriptPath);
	~ScriptLoader();
};

#endif

#endif
