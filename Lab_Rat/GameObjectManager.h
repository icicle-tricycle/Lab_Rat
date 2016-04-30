#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:

	std::vector<GameObject> gameObjects;
	std::map<String, uint> m_map; //Map relating mesh and index

	static GameObjectManager* GetInstance();
	static void ReleaseInstance();

	void AddGameObject(String i_name);

	GameObject GetGameObject(String name);
	GameObject GetGameObject(uint index);
	int GetGameObjectCount();
	void SetPosition(vector3 pos, String name);
	void SetPosition(vector3 pos, uint index);
	void SetVelocity(vector3 vel, String name);
	void SetVelocity(vector3 vel, uint index);
	void SetMaxVelocity(float max, String name);
	void SetMaxVelocity(float max, uint index);

	void Update();
	void Display();

	GameObjectManager();
	~GameObjectManager();
private:
	uint GObjCount = 0;
	static GameObjectManager* instance;
};

