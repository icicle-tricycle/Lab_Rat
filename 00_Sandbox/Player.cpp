#include "Player.h"
#include "InputManager.h"


Player::Player(matrix4 pos, vector3 vel, vector3 accel) 
{
	position = pos;
	velocity = vel;
	acceleration = accel;
	mngr = InputManager.GetInstance();
}
Player::Player(Player const & other) { }
Player & Player::operator=(Player const & other) { return *this; }
Player::~Player() { }

void Player::Update()
{
	//changing the acceleration
	if(mngr->up)
		acceleration.y += 1.0f;
	if(mngr->down)
		acceleration.y -= 1.0f;
	if(mngr->right)
		acceleration.x += 1.0f;
	if(mngr->left)
		acceleration.x -= 1.0f;

	//if no directional inputs, set acc and vel back to 0 so it won't just keep going
	if(!mngr->up && !mngr->down &&!mngr->right && !mngr->left)
	{
		acceleration = vector3(0.0f, 0.0f, 0.0f);
		velocity = vector3(0.0f, 0.0f, 0.0f);
	}
	
	//basic movement stuff
	velocity += acceleration;
	position += glm::translate(velocity);
}