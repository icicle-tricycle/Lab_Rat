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

GameObjectManager::GameObjectManager()
{
	gameObjects = std::vector<GameObject>();
}

GameObjectManager::~GameObjectManager()
{
	ReleaseInstance();
}
