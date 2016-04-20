#pragma once
class BoundingObjectManager
{
public:
	BoundingObjectManager();
	~BoundingObjectManager();

	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();

	void addBox();//a
	void toggleVisibility(int index); //b
	void findIndex(BoundingObjectClass obj);//Get index of BO //c
	void setColor(int index);//d
	void setVisibility(int index);//e
	void renderBO();//f - all BOs
	void renderBO(int index);//f - single BO
	void checkCollisions();//g

private:
	static BoundingObjectManager* instance;
	void resolveCollision(int index1, int index2);
};

