#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"

class ConfigurationFacade
{
public:
	virtual VariableContainer* getVariable(std::string name) = 0;
	virtual void setVariable(std::string name, VariableContainer* variable) = 0;
};