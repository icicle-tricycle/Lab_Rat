#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager()
{
	up = false;
	right = false;
	down = false;
	left = false;
	interact = false;
}

InputManager::~InputManager()
{
	ReleaseInstance();
}

InputManager * InputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}
	return instance;
}

void InputManager::ReleaseInstance()
{
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputManager::updateInputs(bool inputB_up, bool inputB_right, bool inputB_down, bool inputB_left, bool inputB_interact)
{
	up = inputB_up;
	right = inputB_right;
	down = inputB_down;
	left = inputB_left;
	interact = inputB_interact;
}
