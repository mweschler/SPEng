#pragma once
#include <vector>
#include "IGameplayFoundation.h"

class GameObject;

template <typename T>
class GameWorld : public IGameplayFoundation<T> {
public:
	void updateAll();
	int createObject();
	int createObject(int x, int y, int z);
	int deleteObject(int id);
private:
	std::vector<GameObject*> objects;
};