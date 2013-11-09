#include "ScriptingManager.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "Logger.h"
#include "ConfigurationManager.h"
#include "RenderManager.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"
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
		_instance->registerBingings();
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
int LUA_InitLog(lua_State *lua) {
	Logger::Instance()->initialize();
	return 0;
}

int LUA_WriteLog(lua_State *lua) {
	int val = Logger::Instance()->writeToLog(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ShutdownLog(lua_State *lua) {
	Logger::Instance()->shutdown();
	return 0;
}

int LUA_DeleteLog(lua_State *lua) {
	int val = Logger::Instance()->deleteLog();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_GetLogName(lua_State *lua) {
	lua_pushlightuserdata(lua, &(Logger::Instance()->getDataLogName()));
	return 1;
}

int LUA_GetDataLogExists(lua_State *lua) {
	bool exists = Logger::Instance()->getDataLogExists();
	lua_pushlightuserdata(lua, &exists);
	return 1;
}
#pragma endregion

#pragma region ConfigurationManager Wappers
int LUA_SetConfigNumber(lua_State *lua) {
	ConfigurationManager::Instance()->setVariable(lua_tostring(lua, 1), lua_tonumber(lua, 2));
	return 0;
}

int LUA_SetConfigChar(lua_State *lua) {
	string data = lua_tostring(lua, 2);
	ConfigurationManager::Instance()->setVariable(lua_tostring(lua, 1), data.c_str()[0]);
	return 0;
}

int LUA_SetConfigString(lua_State *lua) {
	ConfigurationManager::Instance()->setVariable(lua_tostring(lua, 1), lua_tostring(lua, 2));
	return 0;
}

int LUA_GetConfigInt(lua_State *lua) {
	int val = ConfigurationManager::Instance()->getVariable<int>(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_GetConfigDouble(lua_State *lua) {
	double val = ConfigurationManager::Instance()->getVariable<double>(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_GetConfigFloat(lua_State *lua) {
	float val = ConfigurationManager::Instance()->getVariable<float>(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_GetConfigChar(lua_State *lua) {
	char val = ConfigurationManager::Instance()->getVariable<char>(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_GetConfigString(lua_State *lua) {
	string val = ConfigurationManager::Instance()->getVariable<string>(lua_tostring(lua, 1));
	lua_pushlightuserdata(lua, &val);
	return 1;
}
#pragma endregion

#pragma region Model Wrappers
int LUA_NewModel(lua_State *lua) {
	lua_pushlightuserdata(lua, new Model());
	return 1;
}

int LUA_ModelRelease(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->release();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelIsLoaded(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->release();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelHasVerts(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->hasVerts();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelHasNormals(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->hasNormals();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelHasIndex(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->hasIndex();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelLoadName(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->load(lua_tostring(lua, 2));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelLoadVerts(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->load(*(vector<GLfloat> *)lua_touserdata(lua, 2));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelLoadVertsIndicies(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->load(*(vector<GLfloat> *)lua_touserdata(lua, 2), *(vector<GLushort> *)lua_touserdata(lua, 3));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelLoadVertsNormalsIndicies(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->load(*(vector<GLfloat> *)lua_touserdata(lua, 2), *(vector<GLfloat> *)lua_touserdata(lua, 3), *(vector<GLushort> *)lua_touserdata(lua, 4));
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ModelBind(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	bool val = model->bind((Model::BufferType)lua_tointeger(lua, 2));
	lua_pushlightuserdata(lua, &val);
	return 1;
}
#pragma endregion

#pragma region RenderManager Wrappers
int LUA_RenderManagerIsInitialized(lua_State *lua) {
	bool val = RenderManager::isInitialized();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_DrawModel(lua_State *lua) {
	Model *model = (Model *)lua_touserdata(lua, 1);
	Material *material = (Material *)lua_touserdata(lua, 2);
	//RenderManager::drawModel(*model, *material);
	return 1;
}
#pragma endregion

#pragma region Shader
int LUA_NewShader(lua_State *lua) {
	lua_pushlightuserdata(lua, new Shader());
	return 1;
}

int LUA_ShaderSetType(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	shader->setType((GLenum)lua_touserdata(lua, 2));
	return 0;
}

int LUA_ShaderGetType(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	GLenum type = shader->getType();
	lua_pushlightuserdata(lua, &type);
	return 1;
}

int LUA_ShaderCompile(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	bool val = shader->compile();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ShaderIsCompiled(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	bool val = shader->isCompiled();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ShaderIsLoaded(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	bool val = shader->isLoaded();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ShaderGetId(lua_State *lua) {
	Shader *shader = (Shader *)lua_touserdata(lua, 1);
	GLuint id = shader->getID();
	lua_pushlightuserdata(lua, &id);
	return 1;
}
#pragma endregion

#pragma region ShaderProgram
int LUA_NewShaderProgram(lua_State *lua) {
	lua_pushlightuserdata(lua, new ShaderProgram());
	return 1;
}

int LUA_UseShaderProgram(lua_State *lua) {
	ShaderProgram *shaderProg = (ShaderProgram *)lua_touserdata(lua, 1);
	bool val = shaderProg->use();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_LinkShaderProgram(lua_State *lua) {
	ShaderProgram *shaderProg = (ShaderProgram *)lua_touserdata(lua, 1);
	Shader *vertexShader = (Shader *)lua_touserdata(lua, 2);
	Shader *fragmentShader = (Shader *)lua_touserdata(lua, 3);
	bool val = shaderProg->link(*vertexShader, *fragmentShader);
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ShaderProgramIsLinked(lua_State *lua) {
	ShaderProgram *shaderProg = (ShaderProgram *)lua_touserdata(lua, 1);
	bool val = shaderProg->isLinked();
	lua_pushlightuserdata(lua, &val);
	return 1;
}

int LUA_ReleaseShaderProgram(lua_State *lua) {
	ShaderProgram *shaderProg = (ShaderProgram *)lua_touserdata(lua, 1);
	bool val = shaderProg->release();
	lua_pushlightuserdata(lua, &val);
	return 1;
}
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
	lua_register(_lua, "initLog", LUA_InitLog);
	lua_register(_lua, "writeLog", LUA_WriteLog);
	lua_register(_lua, "shutdownLog", LUA_ShutdownLog);
	lua_register(_lua, "deleteLog", LUA_DeleteLog);
	lua_register(_lua, "getLogName", LUA_GetLogName);
	lua_register(_lua, "getDataLogExists", LUA_GetDataLogExists);
	lua_register(_lua, "setConfigNumber", LUA_SetConfigNumber);
	lua_register(_lua, "setConfigChar", LUA_SetConfigChar);
	lua_register(_lua, "setConfigString", LUA_SetConfigString);
	lua_register(_lua, "getConfigInt", LUA_GetConfigInt);
	lua_register(_lua, "getConfigDouble", LUA_GetConfigDouble);
	lua_register(_lua, "getConfigFloat", LUA_GetConfigFloat);
	lua_register(_lua, "getConfigChar", LUA_GetConfigChar);
	lua_register(_lua, "getConfigString", LUA_GetConfigString);
	lua_register(_lua, "newModel", LUA_NewModel);
	lua_register(_lua, "modelRelease", LUA_ModelRelease);
	lua_register(_lua, "modelIsLoaded", LUA_ModelIsLoaded);
	lua_register(_lua, "modelHasVerts", LUA_ModelHasVerts);
	lua_register(_lua, "modelHasNormals", LUA_ModelHasNormals);
	lua_register(_lua, "modelHasIndex", LUA_ModelHasIndex);
	lua_register(_lua, "modelLoadName", LUA_ModelLoadName);
	lua_register(_lua, "modelLoadVerts", LUA_ModelLoadVerts);
	lua_register(_lua, "modelLoadVertsIndicies", LUA_ModelLoadVertsIndicies);
	lua_register(_lua, "modelLoadVertsNormalsIndicies", LUA_ModelLoadVertsNormalsIndicies);
	lua_register(_lua, "modelBind", LUA_ModelBind);
	lua_register(_lua, "renderManagerIsInitialized", LUA_RenderManagerIsInitialized);
	lua_register(_lua, "drawModels", LUA_DrawModel);
	lua_register(_lua, "newShader", LUA_NewShader);
	lua_register(_lua, "shaderSetType", LUA_ShaderSetType);
	lua_register(_lua, "shaderGetType", LUA_ShaderGetType);
	lua_register(_lua, "shaderCompile", LUA_ShaderCompile);
	lua_register(_lua, "shaderIsCompiled", LUA_ShaderIsCompiled);
	lua_register(_lua, "shaderIsLoaded", LUA_ShaderIsLoaded);
	lua_register(_lua, "shaderGetId", LUA_ShaderGetId);
	lua_register(_lua, "newShaderProgram", LUA_NewShaderProgram);
	lua_register(_lua, "useShaderProgram", LUA_UseShaderProgram);
	lua_register(_lua, "linkShaderProgram", LUA_LinkShaderProgram);
	lua_register(_lua, "shaderProgramIsLinked", LUA_ShaderProgramIsLinked);
	lua_register(_lua, "releaseShaderProgram", LUA_ReleaseShaderProgram);
}
