#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
void SetUp() {
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_dofile(lua, "main.lua");
	lua_close(lua);
}

TEST(Scripting, addObject_defaultLocation){
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_dofile(lua, "main.lua");
	lua_close(lua);
}
