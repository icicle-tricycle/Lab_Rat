#pragma once
#include "GameObject.h"
#include "Trap.h"

class Rat : public GameObject
{
public:
	Rat(String m_sMeshName);
	~Rat();

	std::vector<GameObject*> walls;

	void Update();
	// Only needed for the input manager
	//void Update(bool up, bool right, bool down, bool left, bool interact);

	void WallCollision();
	void SetWalls(std::vector<GameObject*> i_wall);

	void Respawn();
	void CheckTraps(std::vector<Trap*>* traps);
};