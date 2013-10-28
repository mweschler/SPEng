#include "ConfigurationManager.h"

ConfigurationManager* ConfigurationManager::instance = NULL;

//Constructor for ConfigurationManager
ConfigurationManager::ConfigurationManager(){}

ConfigurationManager* ConfigurationManager::Instance()
{
	if(instance == NULL){
		instance = new ConfigurationManager();
	}
	return instance;
}