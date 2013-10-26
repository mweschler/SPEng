#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"

class ConfigurationManager 
{
private:
	std::map <std::string, VariableContainer*> configurationVariables;
public:
	ConfigurationManager(){}
	template <typename T> T getVariable(std::string name){
		return configurationVariables.find(name)->second->getValue<T>();
	}
	template <typename T> void setVariable(std::string name, T newValue){
		VariableContainer* variable = new Variable<T>();
		variable->setValue(newValue);
		configurationVariables[name] = variable;
	}
};