#pragma once
#include "gameobject.h"
#include "InputManager.h"
#include "RE\ReEng.h"

class Player :
	public GameObject
{
public:
	InputManager* mngr;
	
	//Rule of 3
	Player(matrix4 pos, vector3 vel, vector3 accel);
	Player(Player const& other);
	Player& operator=(Player const& other);
	~Player();

	void Update();
};

