#include "GameWorld.h"
#include "GameObject.h"
#include <string>

using namespace std;

GameWorld* GameWorld::_instance = NULL;

// Accesses singleton instance of GameWorld.
GameWorld* GameWorld::Instance() {
	if (!_instance) _instance = new GameWorld();

	return _instance;
}

// Adds a new object to the world at the default location (0, 0, 0).
void GameWorld::createObject(string name) {
	_objects[name] = new GameObject(name);
}

// Adds a new object to the world with specified name and location.
void GameWorld::createObject(string name, int x, int y, int z) {
	_objects[name] = new GameObject(name, x, y, z);
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

}