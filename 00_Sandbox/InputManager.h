#pragma once

class InputManager
{
public:
	InputManager();
	~InputManager();

	static InputManager* GetInstance();
	static void ReleaseInstance();

	bool Up() { return up; };
	bool Right() { return right; };
	bool Down() { return down; };
	bool Left() { return left; };
	bool Interact() { return interact; };

	void updateInputs(bool inputB_up, bool inputB_right, bool inputB_down, bool inputB_left, bool inputB_interact);
private:
	static InputManager* instance;
	bool up;
	bool right;
	bool down;
	bool left;
	bool interact;
};

