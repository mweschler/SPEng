#pragma once
#include <vector>
#include "IGameplayFoundation.h"

class IComponent : ;

class GameObject {
public:
	int addComponent(IComponent *comp);
	int removeComponent(int id);
private:
	std::vector<IComponent*> components;
};