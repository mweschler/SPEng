#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"

template <typename V>
class ConfigurationManager
{
private:
	std::map<std::string, VariableContainer> configurationVariables;
public:
	V retrieveVariable(std::string);
	bool storeVariable(std::string);
	bool modifyVariable(std::string, std::string );
};