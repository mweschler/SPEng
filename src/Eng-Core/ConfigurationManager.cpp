/*#include "ConfigurationManager.h"
#include "ConfigurationFacade.h"
#include "VariableContainer.h"
#include <String>

ConfigurationManager::ConfigurationManager(){}

template <typename T> T ConfigurationManager::getVariable(std::string name)
{
	if(configurationVariables.find(name) == configurationVariables.end())
	{
		return NULL;
	}
	else{
		return configurationVariables.find(name)->getValue<T>();
	}
}

template <typename T> void ConfigurationManager::setVariable(std::string name, T value)
{
	if(configurationVariables.find(name) != configurationVariables.end())
	{
		// Implement type checking in this condition
		configurationVariables.[name]->setValue<T>(value);
	}
	else{
		configurationVariables.[name]->setValue<T>(value);
	}
}*/
