#pragma once
#include "GameObject.h"

class IComponent {
public:
	GameObject* getParent();
	std::string getName();
private:
	std::string _name;
	GameObject* _parent;
};