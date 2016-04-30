#pragma once
#include "MyBoundingObjectClass.h"
#include "RE\ReEngAppClass.h"

class BoundingObjectManager
{
public:

	uint ObjectCount = 0;

	BoundingObjectManager();
	~BoundingObjectManager();

	std::vector<MyBoundingObjectClass*> boundingObjects;
	MeshManagerSingleton* meshMngr = nullptr;
	std::vector<std::vector<int>> collidingIndicies;
	std::map<String, uint> mapIndex;

	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();

	void addBox(std::vector<vector3> a_lListOfVerts, String name); //a
	void toggleVisibilityAABB(int index); //b
	int findIndex(MyBoundingObjectClass obj);//Get index of BO //c
	void reAlign();
	void setColor(int index, vector3 color);//d
	void setVisibility(int index, bool input);//e
	//void renderBO();//f - all BOs
	//void renderBO(int index);//f - single BO
	void checkCollisions();//g

	MyBoundingObjectClass* GetBO(String n_Index);
	MyBoundingObjectClass* GetBO(uint i_Index);
	void SetModelMatrix(matrix4 model, String n_Index);
	//void Update();
	std::vector<int> GetCollidingVector(String n_Index);
	std::vector<int> GetCollidingVector(uint i_Index);
	int GetIndex(String n_Index);

private:
	static BoundingObjectManager* instance;
	void resolveCollision(int index1, int index2);
};

