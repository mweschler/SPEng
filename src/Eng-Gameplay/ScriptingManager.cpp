#include "ScriptingManager.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "Logger.h"
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

// Executes a specific script
void ScriptingManager::executeScript(const char* scriptName) {
	luaL_loadfile(_lua, scriptName);
	lua_call(_lua, 0, 0);
}

#pragma region Lua Wrappers

#pragma region GameWorld Wrappers
// Returns the game world to lua.
int LUA_GetGameWorld(lua_State *lua) {
	lua_pushlightuserdata(lua, GameWorld::Instance);
	return 1;
}

// Clears game world from lua.
int LUA_ClearWorld(lua_State *lua) {
	GameWorld::clearWorld();
	return 0;
}

// Adds an object to the GameWorld with only the name from lua.
int LUA_CreateObjectNameOnly(lua_State *lua) {
	bool result = GameWorld::Instance()->createObject(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &result);
	return 1;
}

// Adds an object to the GameWorld from lua.
int LUA_CreateObject(lua_State *lua) {
	bool result = GameWorld::Instance()->createObject(lua_tostring(lua, 1), lua_tonumber(lua, 2), lua_tonumber(lua, 3), lua_tonumber(lua, 4));
	lua_pushlightuserdata(lua, &result);
	return 1;
}

// Remove an object from the game world via lua
int LUA_DeleteObject(lua_State *lua) {
	GameWorld::Instance()->deleteObject(lua_tostring(lua, 1));
	return 0;
}

// Return a game object to lua.
int LUA_GetObject(lua_State *lua) {
	lua_pushlightuserdata(lua, GameWorld::Instance()->getObject(lua_tostring(lua, 1)));
	return 1;
}

// Update the Game World from lua.
int LUA_UpdateGameWorld(lua_State *lua) {
	GameWorld::Instance()->update();
	return 0;
}
#pragma endregion

#pragma region GameObject Wrappers
// Add acomponent to a game object using lua.
int LUA_AddComponent(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	IComponent *comp = (IComponent *)lua_touserdata(lua, 2);
	gameObj->addComponent(comp);
	return 0;
}

// Remove a component from an object via lua.
int LUA_RemoveComponent(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	gameObj->removeComponent(lua_tostring(lua, 2));
	return 0;
}

// Get a component from an objevct via lua.
int LUA_GetComponent(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	lua_pushlightuserdata(lua, gameObj->getComponent(lua_tostring(lua, 2)));
	return 1;
}

// Set the location of an object using lua.
int LUA_SetLocation(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	gameObj->setLocation(lua_tonumber(lua, 2), lua_tonumber(lua, 3), lua_tonumber(lua, 4));
	return 0;
}

// Get the location of an object using lua.
int LUA_GetLocation(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	lua_pushlightuserdata(lua, gameObj->getLocation());
	return 1;
}

// Get the name of a game object usign lua.
int LUA_GetComponentName(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	lua_pushlightuserdata(lua, &(gameObj->getName()));
	return 1;
}

// Update a game object using lua.
int LUA_UpdateGameObject(lua_State *lua) {
	GameObject *gameObj = (GameObject *)lua_touserdata(lua, 1);
	gameObj->update();
	return 0;
}
#pragma endregion

#pragma region Logger Wrappers

#pragma endregion

#pragma endregion


void ScriptingManager::registerBingings() {
	lua_register(_lua, "getGameWorld", LUA_GetGameWorld);
	lua_register(_lua, "clearWorld", LUA_ClearWorld);
	lua_register(_lua, "createObjectNameOnly", LUA_CreateObjectNameOnly);
	lua_register(_lua, "createObject", LUA_CreateObject);
	lua_register(_lua, "deleteeObject", LUA_DeleteObject);
	lua_register(_lua, "getObject", LUA_GetObject);
	lua_register(_lua, "updateGameWorld", LUA_UpdateGameWorld);
	lua_register(_lua, "addComponent", LUA_AddComponent);
	lua_register(_lua, "removeComponent", LUA_RemoveComponent);
	lua_register(_lua, "getComponent", LUA_GetComponent);
	lua_register(_lua, "setLocation", LUA_SetLocation);
	lua_register(_lua, "getLocation", LUA_GetLocation);
	lua_register(_lua, "getComponentName", LUA_GetComponentName);
	lua_register(_lua, "updateGameObject", LUA_UpdateGameObject);
}