#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance = nullptr;

BoundingObjectManager::BoundingObjectManager()
{
	boundingObjects = std::vector<MyBoundingObjectClass*>();
	ObjectCount = 0;
	meshMngr = MeshManagerSingleton::GetInstance();
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

void BoundingObjectManager::addBox(std::vector<vector3> a_lListOfVerts, String name)
{
	// Original Implementation
	//boundingObjects.push_back(MyBoundingObjectClass(a_lListOfVerts, boundingObjects.size()));
	//gameObjects.push_back(GameObject(name, boundingObjects[boundingObjects.size() - 1].GetModelMatrix(), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), objMass));

	MyBoundingObjectClass* pObject = new MyBoundingObjectClass(a_lListOfVerts);
	if (pObject != nullptr)
	{
		boundingObjects.push_back(pObject);
		mapIndex[name] = ObjectCount;
	}
	ObjectCount = boundingObjects.size();
	std::vector<int> lVector;
	collidingIndicies.push_back(lVector);
	SetModelMatrix(meshMngr->GetModelMatrix(name), name);
}

void BoundingObjectManager::toggleVisibilityAABB(int index)
{
	boundingObjects[index]->IsVisible(!boundingObjects[index]->IsVisible());
}

/*int BoundingObjectManager::findIndex(MyBoundingObjectClass obj)
{
	for (int i = 0; i < boundingObjects.size(); i++) {
		if (obj.GetModelMatrix() == boundingObjects[i]->GetModelMatrix()) {
			return i;
		}
	}
	return -1;
}*/

void BoundingObjectManager::reAlign()
{
	for (int i = 0; i < boundingObjects.size(); i++) {
		boundingObjects[i] = new MyBoundingObjectClass(boundingObjects[i]->GetVertexList());
	}
}

void BoundingObjectManager::setColor(int index, vector3 color)
{
	boundingObjects[index]->SetColor(color);
}

void BoundingObjectManager::setVisibility(int index,bool input)
{
	boundingObjects[index]->SetVisible(input);
}

//void BoundingObjectManager::renderBO()
//{
//	//40% - f
//	//in app.class, kinda, needs to be limited
//}
//
//void BoundingObjectManager::renderBO(int index)
//{
//	//40% - f
//	//nvm, in app.class
//}

void BoundingObjectManager::checkCollisions()
{
	//run through array of objects and see what's colliding
	for (int i = 0; i < boundingObjects.size(); i++)
	{
		for (int j = 0; j < boundingObjects.size(); j++)
		{
			//grab mins and maxes for easy use
			vector3 iMax = vector3(boundingObjects[i]->GetModelMatrix() * vector4(boundingObjects[i]->GetMax(), 1.0f));
			vector3 jMin = vector3(boundingObjects[j]->GetModelMatrix() * vector4(boundingObjects[j]->GetMin(), 1.0f));
			vector3 jMax = vector3(boundingObjects[j]->GetModelMatrix() * vector4(boundingObjects[j]->GetMax(), 1.0f));
			vector3 iMin = vector3(boundingObjects[i]->GetModelMatrix() * vector4(boundingObjects[i]->GetMin(), 1.0f));
																						 
			/*vector3 iMin = boundingObjects[i].GetMin();
			vector3 iMax = boundingObjects[i].GetMax();
			vector3 jMin = boundingObjects[j].GetMin();
			vector3 jMax = boundingObjects[j].GetMax();*/

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
					boundingObjects[i]->SetColor(REGREEN);
					boundingObjects[j]->SetColor(REGREEN);
				}
			}
			else
			{
				boundingObjects[i]->SetColor(REGREEN);
				boundingObjects[j]->SetColor(REGREEN);
			}
		}
	}
}

//void BoundingObjectManager::SetModelMatrix(matrix4 i_matrix, String name)
//{
	/*


	//find the object
	int nIndex = this->GetIndex(a_sIndex);
	if (nIndex < 0) //if not found return
		return;

	m_lObject[nIndex]->SetModelMatrix(a_mModelMatrix);//set the matrix for the indexed Object
	
	
	
	*/
//}

void BoundingObjectManager::resolveCollision(int index1, int index2)
{
	//change colors of BOs (for now, will do physics later)
	boundingObjects[index1]->SetColor(RERED);
	boundingObjects[index2]->SetColor(RERED);
	
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


void BoundingObjectManager::SetModelMatrix(matrix4 model, String n_Index)
{
	int iIndex = this->GetIndex(n_Index);
	if (iIndex < 0)
		return;
	boundingObjects[iIndex]->SetModelMatrix(model);
}

MyBoundingObjectClass* BoundingObjectManager::GetBO(String n_Index)
{
	return GetBO(GetIndex(n_Index));
}

MyBoundingObjectClass* BoundingObjectManager::GetBO(uint i_Index)
{
	if (i_Index < ObjectCount)
		return boundingObjects[i_Index];
	return nullptr;
}

std::vector<int> BoundingObjectManager::GetCollidingVector(String n_Index)
{
	if (GetIndex(n_Index) < 0)
	{
		std::vector<int> empty;
		return empty;
	}
	return GetCollidingVector(GetIndex(n_Index));
}

std::vector<int> BoundingObjectManager::GetCollidingVector(uint i_Index)
{
	if (i_Index >= ObjectCount)
	{
		std::vector<int> empty;
		return empty;
	}
	return collidingIndicies[i_Index];
}

int BoundingObjectManager::GetIndex(String n_Index)
{
	auto var = mapIndex.find(n_Index);
	if (var == mapIndex.end())
		return -1;
	return var->second;
}