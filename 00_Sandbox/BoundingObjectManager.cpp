#include "BoundingObjectManager.h"
#include "MyBoundingObjectClass.h"



BoundingObjectManager::BoundingObjectManager()
{
}


BoundingObjectManager::~BoundingObjectManager()
{
	ReleaseInstance();
}

BoundingObjectManager * BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BoundingObjectManager();
	}
	return instance;
}

void BoundingObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void BoundingObjectManager::addBox()
{
}

void BoundingObjectManager::toggleVisibility(int index)
{
}

void BoundingObjectManager::findIndex(BoundingObjectClass obj)
{
}

void BoundingObjectManager::setColor(int index)
{
}

void BoundingObjectManager::setVisibility(int index)
{
}

void BoundingObjectManager::renderBO()
{
}

void BoundingObjectManager::renderBO(int index)
{
}

void BoundingObjectManager::checkCollisions()
{
	//run through array of objects and see what's colliding

	//if 2 objects are colliding...

	//make sure the indexes aren't identical (object colliding with itself) and do nothing if they are

	//call resolveCollision on the indexes of the colliding objects
}

void BoundingObjectManager::resolveCollision(int index1, int index2)
{
	//for each object...
	
	//calculate vector from center of one object to the other

	//multiply by -1 so vector points away from colliding object

	//normalize

	//add vector to object's velocity so it moves away from the other object and "bounces" off
}
