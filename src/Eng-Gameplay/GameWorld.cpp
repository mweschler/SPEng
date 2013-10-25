#include "GameWorld.h"

GameWorld* GameWorld::_instance = NULL;

GameWorld* GameWorld::Instance() {
	if (!_instance) _instance = new GameWorld();

	return _instance;
}

int GameWorld::createObject() {
	return 0;
}

int GameWorld::createObject(int x, int y, int z) {
	return 0;
}

int GameWorld::deleteObject(int id) {
	return 0;
}

void GameWorld::update() {
}