#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include "RE\ReEng.h"

class GameObject
{
	vector3 position;
	vector3 velocity;
	vector3 acceleration; 
	std::vector<vector3> vertList;

public:
	//Rule of 3
	GameObject();
	GameObject(GameObject const& other);
	GameObject& operator=(GameObject const& other);
	~GameObject();

	vector3 GetPostion();
	vector3 GetVelocity();
	vector3 GetAcceleration();
};

#endif
