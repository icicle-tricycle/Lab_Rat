#pragma once
#include "GameObject.h"
#include "InputManager.h"

class PlayerObject: public GameObject
{
public:
	PlayerObject::PlayerObject(matrix4 pos, vector3 vel, vector3 accel);
	~PlayerObject();

	void Update();

	matrix4 position;
	vector3 velocity;
	vector3 acceleration;

};

