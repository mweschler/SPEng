#include "GameObject.h"
#include "IComponent.h"
#include <string>

using namespace std;

// Constructs GameObject with name and default location (0, 0, 0).
GameObject::GameObject(string name) {
	_name = name;
	_location = new coord();
	_location->x = 0;
	_location->y = 0;
	_location->z = 0;
}

// Constructs GameObject with both specified name and location.
GameObject::GameObject(string name, int x, int y, int z) {
	_name = name;
	_location = new coord();
	_location->x = x;
	_location->y = y;
	_location->z = z;
}

// Adds a specified component.
void GameObject::addComponent(IComponent *comp) {
	_components[comp->getName()] = comp;
	comp->setParent(this);
}

// Removes a speficied component.
int GameObject::removeComponent(string name) {
	_components.erase(name);
	return 0;
}

// Retrieves a specific component by name.
IComponent* GameObject::getComponent(string name) {
	return _components[name];	
}

// Sets the location of the game object.
int GameObject::setLocation(int x, int y, int z) {
	return 0;
}

// Returns the complete location of the game object.
coord* GameObject::getLocation() {
	return _location;
}

// Returns of the name of the given object.
string GameObject::getName() {
	return _name;
}

// Updates all internal components.
void GameObject::update() {
	std::map<string,IComponent*>::iterator it;
	for (std::map<string,IComponent*>::iterator it= _components.begin(); it !=_components.end(); ++it) 
		it->second->update();
}

