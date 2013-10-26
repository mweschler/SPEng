#pragma once
#include <map>
#include "IGameplayFoundation.h"
#include <string>

using namespace std;

class GameObject;

// Models the Game World and provides functionality to modify the game objects.
class GameWorld : public IGameplayFoundation {
public:
	// Accesses singleton instance of GameWorld.
	static GameWorld* Instance();
	
	// Adds a new object to the world at the default location (0, 0, 0).
	void createObject(string name);

	// Adds a new object to the world with specified name and location.
	void createObject(string name, int x, int y, int z);

	// Removed an object from the world with the given name.
	int deleteObject(string name);

	// Returns a reference to a specified game object.
	GameObject* getObject(string name);

	// Updates the state of all objects.
	virtual void update();
private:
	// Maintains a reference of all objects within the world.
	map<string, GameObject*> _objects;

	// The singleton instance of the GameWorld.
	static GameWorld* _instance;

	//Private constructor, copy contructor, and assignment operator for the singleton implementation.
	GameWorld(){};  
	GameWorld(GameWorld const&){};            
	GameWorld& operator=(GameWorld const&){};  
};