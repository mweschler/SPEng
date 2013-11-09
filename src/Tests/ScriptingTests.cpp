#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include "ScriptingManager.h"
#include <stdio.h>
#include "ScriptingManager.h"

TEST(Scripting, addObject_defaultLocation){
	ScriptingManager *script = ScriptingManager::Instance();
	script->executeScript("main.lua");
}
