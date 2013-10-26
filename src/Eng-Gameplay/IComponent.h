#pragma once
#include "GameObject.h"
#include <string>

using namespace std;

// Component Interface to be implemented by all object inner components.
class IComponent {
public:
	// Returns a reference to the containing object.
	GameObject* getParent() { return _parent; };

	// Returns name of the component.
	string getName() { return _name; };

	// Sets the parent of the component.
	void setParent(GameObject* parent) { _parent = parent; };
private:
	// Name of component.
	string _name;

	// Reference to parent.
	GameObject* _parent;
};