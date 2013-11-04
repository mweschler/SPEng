#include "ScriptingManager.h"
#include <string>

using namespace std;

ScriptingManager* ScriptingManager::_instance = NULL;

lua_State* ScriptingManager::_lua = NULL;

// Accesses singleton instance of the ScriptingManager.
ScriptingManager* ScriptingManager::Instance() {
	if (!_instance) {
		_instance = new ScriptingManager();
		_lua = luaL_newstate();
		luaL_openlibs(_lua);
	}

	return _instance;
}

void ScriptingManager::registerBingings() {
}

void ScriptingManager::executeScript(const char* scriptName) {
	luaL_loadfile(_lua, scriptName);
	lua_call(_lua, 0, 0);
}

