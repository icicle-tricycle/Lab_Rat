#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass()
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lListOfVerts)
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

		if (bAreColliding == false)
			return bAreColliding;

		return SAT(a_pOther);
	}
	else
	{
		bAreColliding = false;
		return bAreColliding;
	}
}

bool MyBoundingObjectClass::SAT(MyBoundingObjectClass * const a_pOther)
{
	float ra, rb;
	glm::mat3 R, AbsR;

	// Compute rotation matrix expressing b in a’s coordinate frame
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			R[i][j] = glm::dot(localAxes[i], a_pOther->localAxes[j]);

	// Compute translation vector t
	glm::vec3 t = a_pOther->m_v3CenterG - m_v3CenterG;

	// Bring translation into a’s coordinate frame
	t = glm::vec3(glm::dot(t, localAxes[0]), glm::dot(t, localAxes[1]), glm::dot(t, localAxes[2]));

	// Compute common subexpressions. Add in an epsilon term to
	// counteract arithmetic errors when two edges are parallel and
	// their cross product is (near) null (see text for details)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			AbsR[i][j] = abs(R[i][j]) + .001;

	// Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++) {
		ra = m_v3HalfWidthG[i];
		rb = a_pOther->m_v3HalfWidthG[0] * AbsR[i][0] + a_pOther->m_v3HalfWidthG[1] * AbsR[i][1] + a_pOther->m_v3HalfWidthG[2] * AbsR[i][2];
		if (abs(t[i]) > ra + rb) return 0;
	}

	// Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++) {
		ra = m_v3HalfWidthG[0] * AbsR[0][i] + m_v3HalfWidthG[1] * AbsR[1][i] + m_v3HalfWidthG[2] * AbsR[2][i];
		rb = a_pOther->m_v3HalfWidthG[i];
		if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
	}

	// Test axis L = A0 x B0
	ra = m_v3HalfWidthG[1] * AbsR[2][0] + m_v3HalfWidthG[2] * AbsR[1][0];
	rb = a_pOther->m_v3HalfWidthG[1] * AbsR[0][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[0][1];
	if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;

	// Test axis L = A0 x B1
	ra = m_v3HalfWidthG[1] * AbsR[2][1] + m_v3HalfWidthG[2] * AbsR[1][1];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[0][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[0][0];
	if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;

	// Test axis L = A0 x B2
	ra = m_v3HalfWidthG[1] * AbsR[2][2] + m_v3HalfWidthG[2] * AbsR[1][2];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[0][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[0][0];
	if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;

	// Test axis L = A1 x B0
	ra = m_v3HalfWidthG[0] * AbsR[2][0] + m_v3HalfWidthG[2] * AbsR[0][0];
	rb = a_pOther->m_v3HalfWidthG[1] * AbsR[1][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[1][1];
	if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;

	// Test axis L = A1 x B1
	ra = m_v3HalfWidthG[0] * AbsR[2][1] + m_v3HalfWidthG[2] * AbsR[0][1];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[1][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[1][0];
	if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;

	// Test axis L = A1 x B2
	ra = m_v3HalfWidthG[0] * AbsR[2][2] + m_v3HalfWidthG[2] * AbsR[0][2];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[1][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[1][0];
	if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;

	// Test axis L = A2 x B0
	ra = m_v3HalfWidthG[0] * AbsR[1][0] + m_v3HalfWidthG[1] * AbsR[0][0];
	rb = a_pOther->m_v3HalfWidthG[1] * AbsR[2][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[2][1];
	if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;

	// Test axis L = A2 x B1
	ra = m_v3HalfWidthG[0] * AbsR[1][1] + m_v3HalfWidthG[1] * AbsR[0][1];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[2][2] + a_pOther->m_v3HalfWidthG[2] * AbsR[2][0];
	if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;

	// Test axis L = A2 x B2
	ra = m_v3HalfWidthG[0] * AbsR[1][2] + m_v3HalfWidthG[1] * AbsR[0][2];
	rb = a_pOther->m_v3HalfWidthG[0] * AbsR[2][1] + a_pOther->m_v3HalfWidthG[1] * AbsR[2][0];
	if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;

	//If no tests succeed, they are intersecting
	return true;
}

void MyBoundingObjectClass::DisplayOriented(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(m_m4ToWorld, m_v3Center) *
		glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}

void MyBoundingObjectClass::DisplayReAlligned(vector3 a_v3Color)
{
	m_pMeshMngr->AddCubeToRenderList(glm::translate(IDENTITY_M4, m_v3CenterG) *
		glm::scale(m_v3HalfWidthG * 2.0f), a_v3Color, WIRE);
}
