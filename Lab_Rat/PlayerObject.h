#pragma once
#include "GameObject.h"
#include "InputManager.h"

class PlayerObject: public GameObject
{
public:
	PlayerObject::PlayerObject(vector3 pos, vector3 vel, vector3 accel);
	~PlayerObject();

	void Update();

	vector3 position;
	vector3 velocity;
	vector3 acceleration;

};

