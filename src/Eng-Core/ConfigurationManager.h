#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"
#include "Logger.h"

class ConfigurationManager 
{
private:
	static ConfigurationManager* instance;
	ConfigurationManager();
	ConfigurationManager(ConfigurationManager const&);
	ConfigurationManager& operator=(ConfigurationManager const&);	
	std::map <std::string, VariableContainer*> configurationVariables;
public:
	static ConfigurationManager* Instance();
	template <typename T> T getVariable(std::string name){
		return configurationVariables.find(name)->second->getValue<T>();
	}
	template <typename T> void setVariable(std::string name, T newValue){
		VariableContainer* variable = new Variable<T>();
		variable->setValue(newValue);
		configurationVariables[name] = variable;
	}
};