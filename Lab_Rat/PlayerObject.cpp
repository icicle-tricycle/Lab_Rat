#include "PlayerObject.h"



PlayerObject::PlayerObject(String name, vector3 pos, vector3 vel, vector3 accel, float ObjMass)
	: GameObject(name, pos, vel, accel, ObjMass)
{
	/*position = pos;
	velocity = vel;
	acceleration = accel;*/
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Update()
{
	InputManager * mngr = InputManager::GetInstance();
	//changing the acceleration
	if (mngr->Up())
		acceleration.y += 1.0f;
	if (mngr->Down())
		acceleration.y -= 1.0f;
	if (mngr->Right())
		acceleration.x += 1.0f;
	if (mngr->Left())
		acceleration.x -= 1.0f;

	//if no directional inputs, set acc and vel back to 0 so it won't just keep going
	if (!mngr->Up() && !mngr->Down() && !mngr->Right() && !mngr->Left())
	{
		acceleration = vector3(0.0f, 0.0f, 0.0f);
		velocity = vector3(0.0f, 0.0f, 0.0f);
	}

	//basic movement stuff
	velocity += acceleration;
	position += velocity;
}
