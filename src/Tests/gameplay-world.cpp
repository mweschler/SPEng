#include <iostream>
#include "gtest/gtest.h"
#include "GameWorld.h"
#include "GameObject.h"

TEST(GameWorldTest, addObject_defaultLocation){
	GameWorld* world = GameWorld::Instance();
	bool added = world->createObject("test");
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ(true, added);
	ASSERT_EQ("test", name);
	ASSERT_EQ(0, location->x);
	ASSERT_EQ(0, location->y);
	ASSERT_EQ(0, location->z);

	GameWorld::clearWorld();  
}

TEST(gameworld, addObject_customLocation){
	GameWorld* world = GameWorld::Instance();
	bool added = world->createObject("test", 4, 3, -1);
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ(true, added);
	ASSERT_EQ("test", name);
	ASSERT_EQ(4, location->x);
	ASSERT_EQ(3, location->y);
	ASSERT_EQ(-1, location->z);

	GameWorld::clearWorld();  
}

TEST(gameworld, addObject_duplicateDefault){
	GameWorld* world = GameWorld::Instance();
	bool first = world->createObject("test");
	bool second = world->createObject("test");
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ(true, first);
	ASSERT_EQ(false, second);
	ASSERT_EQ("test", name);
	ASSERT_EQ(0, location->x);
	ASSERT_EQ(0, location->y);
	ASSERT_EQ(0, location->z);

	GameWorld::clearWorld();  
}

TEST(gameworld, addObject_duplicateCustomLocation){
	GameWorld* world = GameWorld::Instance();
	bool first = world->createObject("test", 4, 3, -1);
	bool second = world->createObject("test", 2, -7, 13);
	GameObject* object = world->getObject("test");
	std::string name = object->getName();
	coord* location = object->getLocation();

	ASSERT_EQ(true, first);
	ASSERT_EQ(false, second);
	ASSERT_EQ("test", name);
	ASSERT_EQ(4, location->x);
	ASSERT_EQ(3, location->y);
	ASSERT_EQ(-1, location->z);

	GameWorld::clearWorld();  
}

TEST(gameworld, deleteObject_emptyWorld) {
	GameWorld* world = GameWorld::Instance();
	world->deleteObject("test");
}

