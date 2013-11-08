#include <iostream>
#include "gtest/gtest.h"
#include "Logger.h"
#include <stdio.h>
#include "ScriptingManager.h"

TEST(ScriptingTests, scripttest1) {
	ScriptingManager *script = ScriptingManager::Instance();
	script->executeScript("main.lua");
}

