#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass()
{
	
}


MyBoundingObjectClass::~MyBoundingObjectClass()
{
}

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lListOfVerts, uint dex)
{
	m_vertexList = a_lListOfVerts;
	uint nVertexCount = a_lListOfVerts.size();

	if (nVertexCount > 0)
	{
		m_v3Min = a_lListOfVerts[0];
		m_v3Max = a_lListOfVerts[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (a_lListOfVerts[i].x > m_v3Max.x)
			m_v3Max.x = a_lListOfVerts[i].x;
		else if (a_lListOfVerts[i].x < m_v3Min.x)
			m_v3Min.x = a_lListOfVerts[i].x;

		if (a_lListOfVerts[i].y > m_v3Max.y)
			m_v3Max.y = a_lListOfVerts[i].y;
		else if (a_lListOfVerts[i].y < m_v3Min.y)
			m_v3Min.y = a_lListOfVerts[i].y;

		if (a_lListOfVerts[i].z > m_v3Max.z)
			m_v3Max.z = a_lListOfVerts[i].z;
		else if (a_lListOfVerts[i].z < m_v3Min.z)
			m_v3Min.z = a_lListOfVerts[i].z;
	}

	m_v3Center = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3Center, m_v3Max);

	index = dex;
}

void MyBoundingObjectClass::IsVisible(bool a_bVisible)
{
	m_bVisible = a_bVisible;
}

vector3 MyBoundingObjectClass::GetCentroid(void) { return m_v3Center; }
vector3 MyBoundingObjectClass::GetMin(void) { return m_v3Min; }
vector3 MyBoundingObjectClass::GetMax(void) { return m_v3Max; }
void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld) { m_m4ToWorld = a_m4ToWorld; }
matrix4 MyBoundingObjectClass::GetModelMatrix(void) { return m_m4ToWorld; }

void MyBoundingObjectClass::SetColor(vector3 a_v3Color)
{
	m_v3Color = a_v3Color;
}

void MyBoundingObjectClass::SetVisible(bool input)
{
	m_bVisible = input;
}

bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass * const a_pOther)
{


	//Collision check goes here
	vector3 v3Temp = vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
	vector3 v3Temp1 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Center, 1.0f));

	bool bAreColliding = true;

	//Check if Spheres collide, if they do, check for Box collisions
	if (glm::distance(v3Temp, v3Temp1) < m_fRadius + a_pOther->m_fRadius)
	{
		vector3 vMin1 = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
		vector3 vMax1 = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
		vector3 vMin2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Min, 1.0f));
		vector3 vMax2 = vector3(a_pOther->m_m4ToWorld * vector4(a_pOther->m_v3Max, 1.0f));

		//Check for X
		if (vMax1.x < vMin2.x)
			bAreColliding = false;
		if (vMin1.x > vMax2.x)
			bAreColliding = false;

		//Check for Y
		if (vMax1.y < vMin2.y)
			bAreColliding = false;
		if (vMin1.y > vMax2.y)
			bAreColliding = false;

		//Check for Z
		if (vMax1.z < vMin2.z)
			bAreColliding = false;
		if (vMin1.z > vMax2.z)
			bAreColliding = false;

		return bAreColliding;
	}
	else
	{
		bAreColliding = false;
		return bAreColliding;
	}
}
