#pragma once
#include <map>
#include "IGameplayFoundation.h"
#include "Coord.h"


class IComponent;

// Models an individual object within the game.
class GameObject : public IGameplayFoundation {
public:
	// Constructs GameObject with name and default location (0, 0, 0).
	GameObject(std::string name);

	// Constructs GameObject with both specified name and location.
	GameObject(std::string name, int x, int y, int z);
	
	// Adds a specified component.
	void addComponent(IComponent *comp);

	// Removes a speficied component.
	int removeComponent(std::string name);

	// Retrieves a specific component by name.
	IComponent* getComponent(std::string name);

	// Sets the location of the game object.
	int setLocation(int x, int y, int z);

	// Returns the complete location of the game object.
	coord* getLocation();

	// Returns of the name of the given object.
	std::string getName();

	// Updates all internal components.
	void update();

private:
	// Name of the component.
	std::string _name;

	// Maintains a reference to all components of the system.
	std::map<std::string, IComponent*> _components;

	// Location of the object in the world.
	coord* _location;

	// Default constructor hidden.
	GameObject(){};
};