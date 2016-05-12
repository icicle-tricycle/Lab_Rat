#pragma once
#include "GameObject.h"
#include "Trap.h"

class Rat : public GameObject
{
public:
	Rat(String m_sMeshName);
	~Rat();

	std::vector<GameObject*> walls;
	//std::vector<Trap*>* traps;
	vector3 spawnPoint;
	vector3 deathPoint;
	bool alive;
	float fDyingDuration;

	void Update(double delta);
	// Only needed for the input manager
	//void Update(bool up, bool right, bool down, bool left, bool interact);

	void WallCollision();
	void SetWalls(std::vector<GameObject*> i_wall);

	void SetSpawnPoint(vector3 point);
	void Respawn(vector3 pos);
	//void SetTraps(std::vector<Trap*>* traps);
	//void CheckTraps();
};