#pragma once
#include<string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

// 
class ScriptingManager {
public:
	//! Accesses singleton instance of the ScriptingManager.
	static ScriptingManager* Instance();

	void executeScript(const char* scriptName);

private:
	static void registerBingings();

	//! The singleton instance of the ScriptingManager.
	static ScriptingManager* _instance;

	static lua_State* _lua;

	//!Private constructor, copy contructor, and assignment operator for the singleton implementation.
	ScriptingManager(){};  
	ScriptingManager(ScriptingManager const&){};            
	ScriptingManager& operator=(ScriptingManager const&){};  
};