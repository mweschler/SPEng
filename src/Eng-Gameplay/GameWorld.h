#pragma once
#include <vector>
#include "IGameplayFoundation.h"

class GameObject;

class GameWorld : public IGameplayFoundation {
public:
	static GameWorld* Instance();
	int createObject();
	int createObject(int x, int y, int z);
	int deleteObject(int id);
	virtual void update();
private:
	std::vector<GameObject*> objects;
	GameWorld(){};  // Private so that it can  not be called
	GameWorld(GameWorld const&){};             // copy constructor is private
	GameWorld& operator=(GameWorld const&){};  // assignment operator is private
	static GameWorld* _instance;
};