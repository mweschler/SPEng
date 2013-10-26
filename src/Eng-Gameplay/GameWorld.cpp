#include <string>
#include "GameWorld.h"
#include "GameObject.h"
#include "Logger.h"

using namespace std;

GameWorld* GameWorld::_instance = NULL;

// Accesses singleton instance of GameWorld.
GameWorld* GameWorld::Instance() {
	if (!_instance) _instance = new GameWorld();

	return _instance;
}

// Removes all objects from the game world.
void GameWorld::clearWorld() {
	_instance->_objects.clear();
}

// Adds a new object to the world at the default location (0, 0, 0).
// Returns false if an object with that name already exists.
bool GameWorld::createObject(string name) {
	try {
		_objects.at(name);
		// Exception thrown if element does not exist.
	} catch (const std::out_of_range& oor) {
		_objects[name] = new GameObject(name);
		return true;
	}
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog("An object named " + name + " already exists and cannot be added.");
	return false;
}

// Adds a new object to the world with specified name and location.
// Returns false if an object with that name already exists.
bool GameWorld::createObject(string name, int x, int y, int z) {
	try {
		_objects.at(name);
		// Exception thrown if element does not exist.
	} catch (const std::exception &exc) {
		_objects[name] = new GameObject(name, x, y, z);
		return true;
	}
	Logger* logger = Logger::Instance();
	logger->initialize();
	logger->writeToLog("An object named " + name + " already exists and cannot be added.");
	return false;
}

// Removed an object from the world with the given name.
int GameWorld::deleteObject(string name) {
	_objects.erase(name);
	return 0;
}

////Returns a reference to a specified game object.
GameObject* GameWorld::getObject(string name) {
	return _objects[name];
}

// Updates the state of all objects.
void GameWorld::update() {
	map<string,GameObject*>::iterator it;
	for (map<string,GameObject*>::iterator it= _objects.begin(); it !=_objects.end(); ++it) 
		it->second->update();
}