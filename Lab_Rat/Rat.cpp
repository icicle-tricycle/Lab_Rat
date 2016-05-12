#include "Rat.h"

Rat::Rat(String m_sMeshName) :GameObject(m_sMeshName)
{
	GameObject::Init(m_sMeshName);
	walls = std::vector<GameObject*>();
}

Rat::~Rat()
{
}

void Rat::Update()
{
	GameObject::Update();
	WallCollision();
}

void Rat::WallCollision()
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
}//end wallCollision()


void Rat::SetWalls(std::vector<GameObject*> i_wall)
{
	walls = i_wall;
}

void Rat::Respawn()
{

}

void Rat::CheckTraps(std::vector<Trap*>* traps)
{
	for (uint i = 0; i < traps->size(); i++)
	{
		if (IsColliding(traps->at(i)) && traps->at(i)->GetEnabled())
		{
			traps->at(i)->SetEnabled(false);
			std::cout << "Trap Collision" << std::endl;
		}
	}
}