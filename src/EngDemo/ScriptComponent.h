#pragma once
#include "IComponent.h"
#include <string>

class ScriptComponent: public IComponent{
public:
	ScriptComponent(std::string scriptName);
	virtual void update();
private:
	std::string m_script;
};