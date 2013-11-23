#pragma once
#include <String>
#include <map>
#include "VariableContainer.h"
#include "Logger.h"

using namespace std;

class ConfigurationManager 
{
private:
	static ConfigurationManager* instance;
	ConfigurationManager();
	ConfigurationManager(ConfigurationManager const&);
	ConfigurationManager& operator=(ConfigurationManager const&);	
	std::map <std::string, VariableContainer*> configurationVariables;
	Logger* logger;
public:
	static ConfigurationManager* Instance();

	//Helper method to write to logger
	void writeToLogger (string message){
		logger = Logger::Instance();
		logger->initialize();
		logger->writeToLog(message);
	}

	template <typename T> T getVariable(string name){
		T value;
		try {
			value = configurationVariables.at(name)->getValue<T>();
		} 
		catch (const exception &exc) {
			if(typeid(T) == typeid(string)){
				VariableContainer* variable = new Variable<T>();
				variable->setValue<string>("");
				return variable->getValue<T>();
			}
			else{
				return NULL;
			}
			writeToLogger("Configuration variable " + name + " has not been set");
		}
		return value;
	}

	template <typename T> void setVariable(string name, T newValue){
		VariableContainer* variable = new Variable<T>();
		variable->setValue(newValue);
		configurationVariables[name] = variable;
	}
};