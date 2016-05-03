#pragma once

#include "GameObject.h"

class Trap : GameObject
{
	bool b_isEnabled;

public:

	Trap(String m_sMeshName);

	Trap(Trap const& other);

	Trap& operator=(Trap const& other);

	~Trap(void);

	void Swap(Trap& other);

	bool SetEnabled(bool setTo);
	bool GetEnabled();
private:
};