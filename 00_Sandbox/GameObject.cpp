#include "GameObject.h"
GameObject::GameObject(matrix4 pos, vector3 vel, vector3 accel) 
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
	position += glm::translate(velocity);
}

