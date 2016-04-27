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

	uint index;		//index on the game object vector for the Bounding Manager

	//Rule of 3
	GameObject(matrix4 pos, vector3 vel, vector3 accel, uint dex);
	GameObject(GameObject const& other);
	GameObject& operator=(GameObject const& other);
	~GameObject();

	void Update();
};

#endif
