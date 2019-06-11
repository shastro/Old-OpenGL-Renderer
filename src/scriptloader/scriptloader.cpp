#include "scriptloader.h"

#ifdef USING_LUA

// ScriptLoader
// ------------------------------------------------------

ScriptLoader::ScriptLoader(std::string scriptPath)
{
    // Create a new lua state
    L = luaL_newstate();
    // open all lua standard libs
    luaL_openlibs(L);
    // try to load the actual script
	if (luaL_loadfile(L, scriptPath.c_str()) || lua_pcall(L, 0, 0, 0)) {
        throw ScriptLoaderError("Error loading script");
    }
}

ScriptLoader::~ScriptLoader() {
    // close the script
    if (L) {
        lua_close(L);
    }
}

// LoaderError
// ------------------------------------------------------

ScriptLoaderError::ScriptLoaderError(std::string err)
{
    this->err = err;
}

void ScriptLoaderError::printError()
{
    std::cout << "[ScriptLoaderError] " << err << std::endl;
}

#endif
