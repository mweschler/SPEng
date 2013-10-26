#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"
#include "ConfigurationFacade.h"

class ConfigurationManager 
{
private:
	std::map <std::string, VariableContainer*> configurationVariables;
public:
	ConfigurationManager(){}
	template <typename T> T getVariable(std::string name){
		if(configurationVariables.find(name) == configurationVariables.end())
		{
			return NULL;
		}
		else{
			return configurationVariables.find(name)->second->getValue<T>();
		}
	}
	template <typename T> void setVariable(std::string name, T value){
		if(configurationVariables.find(name) != configurationVariables.end())
		{
			// Implement type checking in this condition
			configurationVariables[name]->setValue<T>(value);
		}
		else{
			configurationVariables[name]->setValue<T>(value);
		}
	}
};