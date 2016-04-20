#pragma once
#ifndef __MYBOUNDINGOBJECTCLASS_H_
#define __MYBOUNDINGOBJECTCLASS_H_

#include "RE\ReEng.h"

class MyBoundingObjectClass
{
	float m_fRadius = 0.0f; //Radius of the Bounding Sphere
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Sphere Class

public:
	
	//Add BO
	MyBoundingObjectClass(std::vector<vector3> a_lListOfVerts);

	//Switch Visibility
	void IsVisible(bool a_bVisible);
	
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



	//Check collision
	bool IsColliding(MyBoundingObjectClass* const a_pOther);

	MyBoundingObjectClass();
	~MyBoundingObjectClass();
};

#endif

