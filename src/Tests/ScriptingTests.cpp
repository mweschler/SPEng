#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>

<<<<<<< HEAD
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
=======

>>>>>>> 742a0bffcb2dcf057dd9786422c5d9fed6dad69b

//TEST(Scripting, addObject_defaultLocation){
//
//}
