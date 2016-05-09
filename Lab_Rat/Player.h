#pragma once
#include "GameObject.h"
#include "InputManager.h"

class Player : public GameObject
{
public:
	Player(String m_sMeshName);
	~Player();


	std::vector<GameObject*> walls;
	InputManager* im = nullptr;
	
	void Update();
	void Update(bool up, bool right, bool down, bool left, bool interact);
	//Checks and then handles collisions with walls
	void WallCollision();

	//I suppose I should redo this as with passing pointer to a vector instead of passing a vector
	void SetWalls(std::vector<GameObject*> i_wall);
};

