#pragma once
#include "gameobject.h"
class Trap :
	public GameObject
{
	bool colliding;		//tracks collision w/ test subject
	bool active;		//is the trap "on"?

public:
	//Rule of 3
	Trap(matrix4 pos, vector3 vel, vector3 accel);
	Trap(Trap const& other);
	Trap& operator=(Trap const& other);
	~Trap();
};

