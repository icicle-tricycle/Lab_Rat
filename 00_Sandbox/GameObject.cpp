#include "GameObject.h"
//Rule of 3
GameObject::GameObject() 
{
	position = vector3(0);
	velocity = vector3(0);
	acceleration = vector3(0);
}
GameObject::GameObject(GameObject const & other) { }
GameObject & GameObject::operator=(GameObject const & other) { return *this; }
GameObject::~GameObject() { }

vector3 GameObject::GetPostion()
{
	return position;
}

vector3 GameObject::GetVelocity()
{
	return velocity;
}

vector3 GameObject::GetAcceleration()
{
	return acceleration;
}

