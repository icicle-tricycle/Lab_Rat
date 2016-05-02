#include "GameObject.h"

void GameObject::Init(String a_sMeshName)
{
	m_v3Velocity = vector3(0.0f, 0.0f, 0.0f);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_sMeshName = a_sMeshName;
	m_uMeshIndex = m_pMeshMngr->IdentifyInstance(m_sMeshName);
	if (m_uMeshIndex >= 0)
	{
		InstanceClass* pInstance = m_pMeshMngr->GetInstanceByName(m_sMeshName);
		m_pBoundingBox = new MyBoundingObjectClass(pInstance->GetVertexList());
	}
}
void GameObject::Swap(GameObject& other)
{
}
void GameObject::Release(void)
{
	SafeDelete(m_pBoundingBox);
}
void GameObject::AddToRenderList(bool a_bAddBox)
{
	if (a_bAddBox)
	{
		if (m_pBoundingBox)
			m_pBoundingBox->AddToRenderList();
		m_pMeshMngr->AddInstanceToRenderList(m_sMeshName);
	}
}
//The big 3
GameObject::GameObject(String a_sMeshName)
{
	Init(a_sMeshName);
}
GameObject::GameObject(GameObject const& other)
{
}
GameObject& GameObject::operator=(GameObject const& other)
{
	if (this != &other)
	{
		Release();
		Init(other.m_sMeshName);
		GameObject temp(other);
		Swap(temp);
	}
	return *this;
}
GameObject::~GameObject(void) { Release(); };
//Accessors
void GameObject::SetModelMatrix(matrix4 a_m4ToWorld)
{
	m_m4ToWorld = a_m4ToWorld;
	m_pBoundingBox->SetModelMatrix(m_m4ToWorld);
	m_pMeshMngr->SetModelMatrix(m_m4ToWorld, m_sMeshName);
}
matrix4 GameObject::GetModelMatrix(void) { return m_m4ToWorld; }
void GameObject::SetVelocity(vector3 a_v3Velocity) { m_v3Velocity = a_v3Velocity; }
vector3 GameObject::GetVelocity(void) { return m_v3Velocity; };
//--- Non Standard Singleton Methods
void GameObject::Update(void)
{
	m_m4ToWorld = m_m4ToWorld * glm::translate(m_v3Velocity);
	SetModelMatrix(m_m4ToWorld);
}
bool GameObject::IsColliding(GameObject * a_pOther)
{
	return m_pBoundingBox->IsColliding(a_pOther->m_pBoundingBox);
}

