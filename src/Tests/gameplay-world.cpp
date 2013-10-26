#include <iostream>
#include "gtest/gtest.h"
#include "GameWorld.h"
#include "GameObject.h"

TEST(gameworld, addObject_defaultLocation){
	GameWorld* world = GameWorld::Instance();
	world->createObject("test");
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ("test", name);
	ASSERT_EQ(0, location->x);
	ASSERT_EQ(0, location->y);
	ASSERT_EQ(0, location->z);
}

TEST(gameworld, addObject_customLocation){
	GameWorld* world = GameWorld::Instance();
	world->createObject("test", 4, 3, -1);
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ("test", name);
	ASSERT_EQ(4, location->x);
	ASSERT_EQ(3, location->y);
	ASSERT_EQ(-1, location->z);
}

TEST(gameworld, deleteObject_emptyWorld) {
	GameWorld* world = GameWorld::Instance();
	world->deleteObject("test");
}

