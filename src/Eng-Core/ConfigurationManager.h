#pragma once
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
	std::map <string, VariableContainer*> configurationVariables;
	Logger* logger;

	//Helper method to write to logger
	void writeToLogger (string message){
		logger = Logger::Instance();
		logger->initialize();
		logger->writeToLog(message);
	}
public:
	static ConfigurationManager* Instance();

	// Retrieves a configuration variable from the map with the given name.
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
			writeToLogger("Cannot retrieve configuration variable " + name + " because it does not exist");
		}
		return value;
	}

	// Sets a configuration variable from the map with the given name.
	template <typename T> void setVariable(string name, T newValue){
		VariableContainer* variable = new Variable<T>();
		variable->setValue(newValue);
		configurationVariables[name] = variable;
	}

	// Removes a configuration variable from the map with the given name.
	template <typename T> void removeVariable(string name) {
		int result = configurationVariables.erase(name);
		if (result == 0) {
			writeToLogger("Cannot remove configuration variable " + name + " because it does not exist");
		}
	}
};