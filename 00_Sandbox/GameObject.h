#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "RE\ReEng.h"

class GameObject
{
public:
	//variables
	matrix4 position;
	vector3 velocity;
	vector3 acceleration;

	//Rule of 3
	GameObject(matrix4 pos, vector3 vel, vector3 accel);
	GameObject(GameObject const& other);
	GameObject& operator=(GameObject const& other);
	~GameObject();

	void Update();
};

#endif
