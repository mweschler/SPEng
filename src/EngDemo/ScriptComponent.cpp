#include "ScriptComponent.h"
#include "ScriptingManager.h"

ScriptComponent::ScriptComponent(std::string scriptName):
	m_script(scriptName)
{
	this->_name = "ScriptComponent";
}

void ScriptComponent::update(){
	ScriptingManager &scriptingManager = *ScriptingManager::Instance();

	scriptingManager.executeScript(m_script.c_str());
}

