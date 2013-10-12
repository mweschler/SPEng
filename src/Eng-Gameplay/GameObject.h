#pragma once
#include <vector>
#include <map>
#include "IGameplayFoundation.h"

class IComponent;

class GameObject : public IGameplayFoundation {
public:
	GameObject(std::string name);
	int addComponent(IComponent *comp);
	int removeComponent(int id);
	std::string getName();
	virtual void update();

private:
	GameObject(){};
	std::string _name;
	std::map<std::string, IComponent*> _components;
};