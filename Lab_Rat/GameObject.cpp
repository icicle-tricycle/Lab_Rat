#include "GameObject.h"
GameObject::GameObject(vector3 pos, vector3 vel, vector3 accel) 
{
	position = pos;
	velocity = vel;
	acceleration = accel;
}
GameObject::GameObject(GameObject const & other) { }
GameObject & GameObject::operator=(GameObject const & other) { return *this; }
GameObject::~GameObject() { }

void GameObject::Update()
{
	velocity += acceleration;
	position += velocity;



	//Transform to the position
	matrix4 m4ToWorld = glm::translate(position);

	MeshManagerSingleton::GetInstance()->SetModelMatrix(m4ToWorld, name);
	BoundingObjectManager::GetInstance()->SetModelMatrix(m4ToWorld, name);
}

void GameObject::Display()
{
	MeshManagerSingleton::GetInstance()->AddInstanceToRenderList(name);
}

