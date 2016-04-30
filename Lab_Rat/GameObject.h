#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "BoundingObjectManager.h"

class GameObject
{
public:
	//variables
	vector3 position;
	vector3 velocity;
	vector3 acceleration;
	String name = "";
	

	//Rule of 3
	GameObject(vector3 pos, vector3 vel, vector3 accel);
	GameObject(GameObject const& other);
	GameObject& operator=(GameObject const& other);
	~GameObject();

	void Update();
	void Display();
};

#endif
