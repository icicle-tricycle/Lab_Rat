#pragma once
#include "MyBoundingObjectClass.h"
#include <vector>
#include "RE\ReEngAppClass.h"

class BoundingObjectManager
{
public:
	BoundingObjectManager();
	~BoundingObjectManager();

	std::vector<MyBoundingObjectClass> boundingObjects;

	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();

	void addBox(std::vector<vector3> a_lListOfVerts);//a
	void toggleVisibilityAABB(int index); //b
	void findIndex(BoundingObjectClass obj);//Get index of BO //c
	void setColor(int index, vector3 color);//d
	void setVisibility(int index, bool input);//e
	//void renderBO();//f - all BOs
	//void renderBO(int index);//f - single BO
	void checkCollisions();//g

private:
	static BoundingObjectManager* instance;
	void resolveCollision(int index1, int index2);
};

