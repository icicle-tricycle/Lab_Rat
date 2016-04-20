#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;

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

void BoundingObjectManager::setColor(int index, vector3 color)
{
	boundingObjects[index].SetColor(color);
}

void BoundingObjectManager::setVisibility(int index,bool input)
{
	boundingObjects[index].SetVisible(input);
}

void BoundingObjectManager::renderBO()
{
}

void BoundingObjectManager::renderBO(int index)
{
}

void BoundingObjectManager::checkCollisions()
{
}

void BoundingObjectManager::resolveCollision(int index1, int index2)
{
}
