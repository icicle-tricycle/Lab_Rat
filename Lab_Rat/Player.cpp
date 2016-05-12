#include "Player.h"



Player::Player(String m_sMeshName) : GameObject(m_sMeshName)
{
	GameObject::Init(m_sMeshName);
	walls = std::vector<GameObject*>();
	jumped = false;
}


Player::~Player()
{
}


void Player::Update()
{
	im = InputManager::GetInstance();
	Update(im->Up(), im->Right(), im->Down(), im->Left(), im->Interact());
}
void Player::Update(bool up, bool right, bool down, bool left, bool interact)
{
	if (interact && !jumped)
	{
		//m_v3Velocity.y = 0.75f;
		jumped = true;
	}

	//change velocity based on input
	m_v3Velocity = vector3(
		0.1f*(float)(right - left),
		m_v3Velocity.y * 0.8f,
		0.1f*(float)(down - up)
		);


	GameObject::Update();
	//test collisions
	WallCollision();

	//hacky floor stuff, since currently wallColision() doesn't allow a player to move parallel to a surface

	//saving correct velocity
	vector3 tempV = m_v3Velocity;
	//move back
	m_v3Velocity = -tempV;
	GameObject::Update();
	//fall from the acceptable position
	m_v3Velocity = vector3(
		tempV.x,
		tempV.y -0.05f,
		tempV.z
		);
	GameObject::Update();
	//if we collide with a wall, don't fall
	for (uint i = 0; i < walls.size(); i++)
	{
		if (IsColliding(walls.at(i)))
		{
			jumped = false;
			//move back
			m_v3Velocity = vector3(
				-m_v3Velocity.x,
				-(m_v3Velocity.y),
				-m_v3Velocity.z
				);
			GameObject::Update();
			m_v3Velocity = vector3(
				-m_v3Velocity.x,
				0.0f,
				-m_v3Velocity.z
				);
			GameObject::Update();
		}
	}
	

	
}

//Check collisions with objects in our wall collection. Assumes player has moved just before this function call.
void Player::WallCollision()
{
	for (uint i = 0; i < walls.size(); i++)
	{
		//vector3 posBeforeFrame = m_pBoundingBox->GetCenterGlobal();
		vector3 velThisFrame = m_v3Velocity;

		float tempVelx = 0;
		float tempVely = 0;
		float tempVelz = 0;

		//If we're colliding,
		if (IsColliding(walls.at(i)))
		{
			//move back
			m_v3Velocity = -m_v3Velocity;
			GameObject::Update();

			//check x
			for (uint x = 0; x < 20; x++)
			{
				//move 5% * x forward
				tempVelx = velThisFrame.x * x / 20;
				m_v3Velocity = vector3(tempVelx, 0.0f, 0.0f);
				GameObject::Update();
				//If we're not colliding,
				if (!IsColliding(walls.at(i)))
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
				}
				//if we collide, go back a step and break
				else
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
					//Save the last move that worked
					tempVelx = velThisFrame.x  * (x - 1) / 20;
					m_v3Velocity = vector3(tempVelx, 0.0f, 0.0f);
					break;
				}
			}
			//check y
			for (uint y = 0; y < 20; y++)
			{
				//move 5% * x forward
				tempVely = velThisFrame.y * y / 20;
				m_v3Velocity = vector3(tempVelx, tempVely, 0.0f);
				GameObject::Update();
				//If we're not colliding,
				if (!IsColliding(walls.at(i)))
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
				}
				//if we collide, go back a step and break
				else
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
					//Save the last move that worked
					//tempVely = velThisFrame.y  * (y - 1) / 20;
					//tempVely = -7345342.5f;
					m_v3Velocity = vector3(tempVelx, tempVely, 0.0f);
					break;
				}
			}
			//check z
			for (uint z = 0; z < 20; z++)
			{
				//move 5% * x forward
				tempVelz = velThisFrame.z * z / 20;
				m_v3Velocity = vector3(tempVelx, tempVely, tempVelz);
				GameObject::Update();
				//If we're not colliding,
				if (!IsColliding(walls.at(i)))
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
				}
				//if we collide, go back a step and break
				else
				{
					//move back
					m_v3Velocity = -m_v3Velocity;
					GameObject::Update();
					//Save the last move that worked
					tempVelz = velThisFrame.z  * (z - 1) / 20;
					m_v3Velocity = vector3(tempVelx, tempVely, tempVelz);
					break;
				}
			}//end z check
		}//end specific wall check
	}//end checking all walls
} //end wallCollision()


void Player::ButtonCollision()
{


}



void Player::SetWalls(std::vector<GameObject*> i_wall)
{
	walls = i_wall;
}

