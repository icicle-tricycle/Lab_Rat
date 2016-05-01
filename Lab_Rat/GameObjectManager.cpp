#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager * GameObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameObjectManager();
	}
	return instance;
}

void GameObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameObjectManager::AddGameObject(String i_name)
{
	GameObject* temp = new GameObject(i_name);
}

void GameObjectManager::AddGameObject(String i_name, vector3 i_pos, float i_mass)
{
	GameObject* temp = new GameObject(i_name, i_pos, i_mass);
}

GameObjectManager::GameObjectManager()
{
	gameObjects = std::vector<GameObject>();
}

GameObjectManager::~GameObjectManager()
{
	ReleaseInstance();
}
