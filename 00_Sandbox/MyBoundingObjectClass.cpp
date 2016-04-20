#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass()
{
	m_fRadius = 0.0f;
	m_m4ToWorld = IDENTITY_M4;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
}


MyBoundingObjectClass::~MyBoundingObjectClass()
{
}

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> a_lListOfVerts)
{
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



matrix4 MyBoundingObjectClass::GetModelMatrix(void) { return m_m4ToWorld; }
