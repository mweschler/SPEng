#pragma once
#include <map>
#include "VariableContainer.h"
#include "Logger.h"

using namespace std;

/*! Configuration Manager class to be used to store and retrieve engine configuration variables
*/
class ConfigurationManager 
{
private:
	static ConfigurationManager* instance;
	ConfigurationManager();
	ConfigurationManager(ConfigurationManager const&);
	ConfigurationManager& operator=(ConfigurationManager const&);	
	std::map <string, VariableContainer*> configurationVariables;
	Logger* logger;
	void writeToLogger (string message){
		logger = Logger::Instance();
		logger->initialize();
		logger->writeToLog(message);
	}
public:
	/*! Retrieves an instance of the Configuration Manager. Creates one if it does not exist 
		but maintains at most one during the execution of the game engine
	*/
	static ConfigurationManager* Instance();
	/*! Retrieves a configuration variable the given name. If the variable does not 
		exist, it returns a null value or an empty pointer depending on the template
		type
		\param name The name of the configuration variable to retrieve
	*/
	template <typename T> T getVariable(string name){
		T value;
		try {
			value = configurationVariables.at(name)->getValue<T>();
		} 
		catch (const exception &exc) {
			writeToLogger("Cannot retrieve configuration variable " + name + " because it does not exist");
			if(typeid(T) == typeid(string)){
				VariableContainer* variable = new Variable<T>();
				variable->setValue<string>("");
				return variable->getValue<T>();
			}
			else{
				return NULL;
			}
		}
		return value;
	}

	/*! Sets a configuration variable with the given name. If the variable does not
		exist, it creates a new one with the new value. If it does exist, the method
		will update its value
		\param name The name of the configuration variable to set
		\param newValue The new value of the variable that will replace the old value
	*/
	template <typename T> void setVariable(string name, T newValue){
		VariableContainer* variable = new Variable<T>();
		variable->setValue(newValue);
		configurationVariables[name] = variable;
	}

	/*! Removes a configuration variable with the given name. If the variable does not
		exist, it logs an error using the logger
		\param name The name of the configuration variable to remove
	*/
	template <typename T> void removeVariable(string name) {
		int result = configurationVariables.erase(name);
		if (result == 0) {
			writeToLogger("Cannot remove configuration variable " + name + " because it does not exist");
		}
	}
};