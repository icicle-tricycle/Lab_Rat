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
	//run through array of objects and see what's colliding
	for (int i = 0; i < boundingObjects.size(); i++)
	{
		for (int j = 0; j < boundingObjects.size(); j++)
		{
			//grab mins and maxes for easy use
			vector3 iMin = vector3(boundingObjects[i].GetModelMatrix() * vector4(boundingObjects[i].GetMin(), 1.0f));
			vector3 iMax = vector3(boundingObjects[i].GetModelMatrix() * vector4(boundingObjects[i].GetMax(), 1.0f));
			vector3 jMin = vector3(boundingObjects[j].GetModelMatrix() * vector4(boundingObjects[j].GetMin(), 1.0f));
			vector3 jMax = vector3(boundingObjects[j].GetModelMatrix() * vector4(boundingObjects[j].GetMax(), 1.0f));

			if ((iMin.x > jMin.x && iMin.x < jMax.x)||
				(iMax.x > jMin.x && iMax.x < jMax.x)&&
				(iMin.y > jMin.y && iMin.y < jMax.y) ||
				(iMax.y > jMin.y && iMax.y < jMax.y)&&
				(iMin.z > jMin.z && iMin.z < jMax.z) ||
				(iMax.z > jMin.z && iMax.z < jMax.z))
			{
				//make sure the indexes aren't identical (object colliding with itself) and do nothing if they are
				if (i != j)
				{
					//call resolveCollision on the indexes of the colliding objects
					resolveCollision(i, j);
				}
				else
				{
					boundingObjects[i].SetColor(REGREEN);
					boundingObjects[j].SetColor(REGREEN);
				}
			}
			else
			{
				boundingObjects[i].SetColor(REGREEN);
				boundingObjects[j].SetColor(REGREEN);
			}
		}
	}
}

void BoundingObjectManager::resolveCollision(int index1, int index2)
{
	//change colors of BOs (for now, will do physics later)
	boundingObjects[index1].SetColor(RERED);
	boundingObjects[index2].SetColor(RERED);
	
	/* physics stuff to make objects bounce away from each other - currently nonfunctional due to scope issues
	
	//for each object...
	
	//get centroid
	vector3 centroid1 = vector3(boundingObjects[index1].GetModelMatrix() * vector4(boundingObjects[index1].GetCentroid(), 1.0f));
	vector3 centroid2 = vector3(boundingObjects[index2].GetModelMatrix() * vector4(boundingObjects[index2].GetCentroid(), 1.0f));

	//calculate vector from centroid of one object to the other
	vector3 toward1 = centroid1 - centroid2;
	vector3 toward2 = centroid2 - centroid1;

	//multiply by -1 so vector points away from colliding object
	toward1 *= -1;
	toward2 *= -2;

	//normalize
	toward1 /= toward1.length;
	toward2 /= toward2.length;

	//add vector to object's velocity so it moves away from the other object and "bounces" off (can't be done now because BOs not set to move right now)

	*/
}
