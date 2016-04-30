#ifndef __MYBOUNDINGOBJECTCLASS_H_
#define __MYBOUNDINGOBJECTCLASS_H_

#include "RE\ReEng.h"

class MyBoundingObjectClass
{
	bool m_bVisible = true;
	float m_fRadius = 0.0f; //Radius of the Bounding Sphere

	MeshManagerSingleton* m_pMeshMngr = nullptr;
	
	std::vector<vector3> m_vertexList = std::vector<vector3>(0.0f);

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Sphere Class
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Color = REGREEN;
	
	//bool m_bVisible = true;

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the Object Class
	
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

	vector3 localAxes[3] = { vector3(1, 0, 0), vector3(0, 1, 0), vector3(0, 0, 1) }; //Should store the local axes of the bounding object

public:
	
	//Add BO
	MyBoundingObjectClass(std::vector<vector3> a_lListOfVerts);

	//Switch Visibility
	void IsVisible(bool a_bVisible);
	bool IsVisible() { return m_bVisible; };
	
	//Get Centroid
	vector3 GetCentroid(void);

	//Get min of BO
	vector3 GetMin(void);

	//Get max of BO
	vector3 GetMax(void);

	//Set model to world matrix of BO
	void SetModelMatrix(matrix4 a_m4ToWorld);

	//Get model to world matrix of BO
	matrix4 GetModelMatrix();

	//Set color of BO
	void SetColor(vector3 a_v3Color);

	//set visibility
	void SetVisible(bool input);

	//Check collision
	bool IsColliding(MyBoundingObjectClass* const a_pOther);
	bool SAT(MyBoundingObjectClass* const a_pOther);

	//Display
	void DisplayOriented(vector3 a_v3Color = REDEFAULT);
	void DisplayReAlligned(vector3 a_v3Color = REDEFAULT);

	//Get vertex list
	std::vector<vector3> GetVertexList() { return m_vertexList; }

	MyBoundingObjectClass();
	~MyBoundingObjectClass();
};

#endif

